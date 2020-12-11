[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2Fritaswc%2Fzx-ip-address.svg?type=shield)](https://app.fossa.com/projects/git%2Bgithub.com%2Fritaswc%2Fzx-ip-address?ref=badge_shield)
[![Build Status](https://www.travis-ci.org/ritaswc/zx-ip-address.svg?branch=master)](https://www.travis-ci.org/ritaswc/zx-ip-address)
<a href="https://packagist.org/packages/ritaswc/zx-ip-address"><img src="https://img.shields.io/packagist/dt/ritaswc/zx-ip-address" alt="Total Downloads"></a>
<a href="https://packagist.org/packages/ritaswc/zx-ip-address"><img src="https://img.shields.io/packagist/v/ritaswc/zx-ip-address" alt="Latest Stable Version"></a>
<a href="https://packagist.org/packages/ritaswc/zx-ip-address"><img src="https://img.shields.io/packagist/l/ritaswc/zx-ip-address" alt="License"></a>


## ZxIpAddress with Chunzhen(cz88.net) 
##### Being updating every <font color=#FF0000 size=36>5</font> days

### IPv4 address locations by 纯真网络
database updated at <font color=#FF0000 size=36>2020-12-10</font> with <font color=#FF0000 size=36>528128</font> records

### IPv6 address locations by Zx Inc.
database updated at <font color=#FF0000 size=36>2020-05-06</font> with <font color=#FF0000 size=36>140993</font> records

### Usage
```shell script
composer require ritaswc/zx-ip-address
```
Your code:
```php
$result = \Ritaswc\ZxIPAddress\IPv4Tool::query('114.114.114.114');
/*
$result = [
    "start" => "114.114.114.114"
    "end" => "114.114.114.114"
    "addr" => array:2 [
        0 => "江苏省南京市"
        1 => "南京信风网络科技有限公司GreatbitDNS服务器"
    ]
    "disp" => "江苏省南京市 南京信风网络科技有限公司GreatbitDNS服务器"
]
 */
```

```php
$result = \Ritaswc\ZxIPAddress\IPv6Tool::query('240e:e9:8819:0:3::3f9');
/*
$result = [
    "start" => "240e:e9:8800::"
    "end" => "240e:e9:8fff:ffff::"
    "addr" => array:2 [
        0 => "中国江苏省苏州市"
        1 => "中国电信IDC"
    ]
    "disp" => "中国江苏省苏州市 中国电信IDC"
]
 */
```

### Official Website
- [纯真IPv4数据库](http://www.cz88.net/ip/)
- [IPv6地址查询工具 Tokyo Japan](http://ip.zxinc.org)
- [IPv6地址查询工具 Ningbo China](https://ip.shanshan-business.com)
- [IPv6地址查询工具 Beijing China](https://ip.yinghualuo.cn)

### Author Blog
- [Charles的小星球](https://blog.yinghualuo.cn)

### QQ Group
- ZX IPv6地址库交流群   23871048

### Sponsor
![QrCode](https://blog.yinghualuo.cn/blog/2020/11/sponsor.png)

### License
ZxIpAddress is licensed under [MIT](https://github.com/ritaswc/zx_ip_address/blob/master/LICENSE).

[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2Fritaswc%2Fzx-ip-address.svg?type=large)](https://app.fossa.com/projects/git%2Bgithub.com%2Fritaswc%2Fzx-ip-address?ref=badge_large)
