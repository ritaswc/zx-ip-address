<?php


namespace Ritaswc\ZxIPAddress;

/**
 * @deprecated see https://github.com/ZX-Inc/zxipdb-php
 */
class IPTool
{
    public static function query($ip)
    {
        switch (true) {
            case IPv4Tool::isValidAddress($ip):
                return IPv4Tool::query($ip);
            case  IPv6Tool::isValidAddress($ip):
                return IPv6Tool::query($ip);
        }
        throw new InvalidIpAddressException("Invalid IP address:{$ip}");
    }

    public static function total()
    {
        return [
            'IPv4' => IPv4Tool::total(),
            'IPv6' => IPv6Tool::total(),
        ];
    }
}