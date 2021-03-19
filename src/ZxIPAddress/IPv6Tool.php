<?php

namespace Ritaswc\ZxIPAddress;

class IPv6Tool
{
    const FILE = __DIR__ . '/../database/ipv6wry.db';
    const FORMAT = 'J2';
    private static $total = null;
    // 索引区
    private static $index_start_offset;
    private static $index_end_offset;
    private static $offlen;
    private static $iplen;
    private static $has_initialized = false;

    /**
     * return database record count
     * @return int|string
     */
    public static function total()
    {
        if (null === static::$total) {
            $fd = fopen(static::FILE, 'rb');
            static::initialize($fd);
            fclose($fd);
        }
        return static::$total;
    }

    /**
     * judge IP address is valid
     * @param $ip
     * @return bool
     */
    public static function isValidAddress($ip)
    {
        return $ip === filter_var($ip, FILTER_VALIDATE_IP, FILTER_FLAG_IPV6);
    }

    public static function initialize($fd)
    {
        if (!static::$has_initialized) {
            if (PHP_INT_SIZE < 8) {
                throw new RuntimeException('64bit OS supported only');
            }
            if (version_compare(PHP_VERSION, "5.6", "<")) {
                throw new RuntimeException('php version 5.6 or greater');
            }
            static::$index_start_offset = static::read8($fd, 16);
            static::$offlen = static::read1($fd, 6);
            static::$iplen = static::read1($fd, 7);
            static::$total = static::read8($fd, 8);
            static::$index_end_offset = static::$index_start_offset
                + (static::$iplen + static::$offlen) * static::$total;
            static::$has_initialized = true;
        }
    }

    /**
     * query ipv6
     * @param $ip
     * @return array
     */
    public static function query($ip)
    {
        if (!self::isValidAddress($ip)) {
            throw new RuntimeException("error IPv6 address: $ip");
        }
        $ip_bin = inet_pton($ip);
        $fd = fopen(static::FILE, 'rb');
        static::initialize($fd);
        $ip_num_arr = unpack(static::FORMAT, $ip_bin);
        // IP地址前半部分转换成有int
        $ip_num1 = $ip_num_arr[1];
        // IP地址后半部分转换成有int
        $ip_num2 = $ip_num_arr[2];
        $ip_find = static::find($fd, $ip_num1, $ip_num2, 0, static::$total);
        $ip_offset = static::$index_start_offset + $ip_find * (static::$iplen + static::$offlen);
        $ip_offset2 = $ip_offset + static::$iplen + static::$offlen;
        $ip_start = inet_ntop(pack(static::FORMAT, static::read8($fd, $ip_offset), 0));
        try {
            $ip_end = inet_ntop(pack(static::FORMAT, static::read8($fd, $ip_offset2) - 1, 0));
        } catch (RuntimeException $e) {
            $ip_end = "FFFF:FFFF:FFFF:FFFF::";
        }
        $ip_record_offset = static::read8($fd, $ip_offset + static::$iplen, static::$offlen);
        $ip_addr = static::read_record($fd, $ip_record_offset);
        $ip_addr_disp = $ip_addr[0] . " " . $ip_addr[1];
        if (is_resource($fd)) {
            fclose($fd);
        }
        return array("start" => $ip_start, "end" => $ip_end, "addr" => $ip_addr, "disp" => $ip_addr_disp);
    }

    /**
     * 读取记录
     * @param $fd
     * @param $offset
     * @return string[]
     */
    public static function read_record($fd, $offset)
    {
        $record = array(0 => "", 1 => "");
        $flag = static::read1($fd, $offset);
        if ($flag == 1) {
            $location_offset = static::read8($fd, $offset + 1, static::$offlen);
            return static::read_record($fd, $location_offset);
        }
        $record[0] = static::read_location($fd, $offset);
        if ($flag == 2) {
            $record[1] = static::read_location($fd, $offset + static::$offlen + 1);
        } else {
            $record[1] = static::read_location($fd, $offset + strlen($record[0]) + 1);
        }
        return $record;
    }

    /**
     * 读取地区
     * @param $fd
     * @param $offset
     * @return string
     */
    public static function read_location($fd, $offset)
    {
        if ($offset == 0) {
            return "";
        }
        $flag = static::read1($fd, $offset);
        // 出错
        if ($flag == 0) {
            return "";
        }
        // 仍然为重定向
        if ($flag == 2) {
            $offset = static::read8($fd, $offset + 1, static::$offlen);
            return static::read_location($fd, $offset);
        }
        return static::readstr($fd, $offset);
    }

    /**
     * 查找 ip 所在的索引
     * @param $fd
     * @param $ip_num1
     * @param $ip_num2
     * @param $l
     * @param $r
     * @return mixed
     */
    public static function find($fd, $ip_num1, $ip_num2, $l, $r)
    {
        if ($l + 1 >= $r) {
            return $l;
        }
        $m = intval(($l + $r) / 2);
        $m_ip1 = static::read8($fd, static::$index_start_offset + $m * (static::$iplen + static::$offlen), static::$iplen);
        $m_ip2 = 0;
        if (static::$iplen <= 8) {
            $m_ip1 <<= 8 * (8 - static::$iplen);
        } else {
            $m_ip2 = static::read8($fd, static::$index_start_offset + $m * (static::$iplen + static::$offlen) + 8, static::$iplen - 8);
            $m_ip2 <<= 8 * (16 - static::$iplen);
        }
        if (static::uint64cmp($ip_num1, $m_ip1) < 0) {
            return static::find($fd, $ip_num1, $ip_num2, $l, $m);
        }
        if (static::uint64cmp($ip_num1, $m_ip1) > 0) {
            return static::find($fd, $ip_num1, $ip_num2, $m, $r);
        }
        if (static::uint64cmp($ip_num2, $m_ip2) < 0) {
            return static::find($fd, $ip_num1, $ip_num2, $l, $m);
        }
        return static::find($fd, $ip_num1, $ip_num2, $m, $r);
    }

    public static function readraw($fd, $offset = null, $size = 0)
    {
        if (!is_null($offset)) {
            fseek($fd, $offset);
        }
        return fread($fd, $size);
    }

    public static function read1($fd, $offset = null)
    {
        if (!is_null($offset)) {
            fseek($fd, $offset);
        }
        $a = fread($fd, 1);
        return @unpack("C", $a)[1];
    }

    public static function read8($fd, $offset = null, $size = 8)
    {
        if (!is_null($offset)) {
            fseek($fd, $offset);
        }
        $a = fread($fd, $size) . "\0\0\0\0\0\0\0\0";
        return @unpack("P", $a)[1];
    }

    public static function readstr($fd, $offset = null)
    {
        if (!is_null($offset)) {
            fseek($fd, $offset);
        }
        $str = "";
        $chr = static::read1($fd, $offset);
        while ($chr != 0) {
            $str .= chr($chr);
            $offset++;
            $chr = static::read1($fd, $offset);
        }
        return $str;
    }

    public static function ip2num($ip)
    {
        return unpack("N", inet_pton($ip))[1];
    }

    public static function inet_ntoa($nip)
    {
        $ip = array();
        for ($i = 3; $i > 0; $i--) {
            $ip_seg = intval($nip / pow(256, $i));
            $ip[] = $ip_seg;
            $nip -= $ip_seg * pow(256, $i);
        }
        $ip[] = $nip;
        return join(".", $ip);
    }

    public static function uint64cmp($a, $b)
    {
        if ($a >= 0 && $b >= 0 || $a < 0 && $b < 0) {
            if ($a === $b) {
                return 0;
            }
            if ($a > $b) {
                return 1;
            }
            return -1;
        }
        if ($a >= 0 && $b < 0) {
            return -1;
        }
        return 1;
    }
}