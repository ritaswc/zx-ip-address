<?php
date_default_timezone_set("PRC");
$copywrite = file_get_contents("http://update.cz88.net/ip/copywrite.rar");

$qqwry = file_get_contents("http://update.cz88.net/ip/qqwry.rar");

if (!$copywrite || !$qqwry) {
    exit(1);
}



$key = unpack("V6", $copywrite)[6];
for ($i = 0; $i < 0x200; $i++) {
    $key *= 0x805;
    $key++;
    $key = $key & 0xFF;
    $qqwry[$i] = chr(ord($qqwry[$i]) ^ $key);
}
$qqwry = gzuncompress($qqwry);

file_put_contents('src/database/ipv4wry.db', $qqwry);

$date = $copywrite[41] . $copywrite[42] . $copywrite[43] . $copywrite[44] . '-' . $copywrite[47] . $copywrite[48] . '-' . $copywrite[51] . $copywrite[52];


echo $date;