[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2Fritaswc%2Fzx-ip-address.svg?type=shield)](https://app.fossa.com/projects/git%2Bgithub.com%2Fritaswc%2Fzx-ip-address?ref=badge_shield)
[![Build Status](https://www.travis-ci.org/ritaswc/zx-ip-address.svg?branch=master)](https://www.travis-ci.org/ritaswc/zx-ip-address)
<a href="https://packagist.org/packages/ritaswc/zx-ip-address"><img src="https://img.shields.io/packagist/dt/ritaswc/zx-ip-address" alt="Total Downloads"></a>
<a href="https://packagist.org/packages/ritaswc/zx-ip-address"><img src="https://img.shields.io/packagist/v/ritaswc/zx-ip-address" alt="Latest Stable Version"></a>
<a href="https://packagist.org/packages/ritaswc/zx-ip-address"><img src="https://img.shields.io/packagist/l/ritaswc/zx-ip-address" alt="License"></a>


## IPv4/IPv6 offline address database.IPv4/IPv6双栈地址离线数据库。IPv4 by 纯真网络，IPv6 by ZX Inc.
##### Being updating every <font color=#FF0000 size=36>5</font> days 每<font color=#FF0000 size=36>5</font>天更新一次

### IPv4 address locations by 纯真网络
database updated at <font color=#FF0000 size=36>2020-12-18</font> with <font color=#FF0000 size=36>528137</font> records

### IPv6 address locations by Zx Inc.
database updated at <font color=#FF0000 size=36>2020-05-06</font> with <font color=#FF0000 size=36>140993</font> records

### Usage使用方法
```shell script
composer require ritaswc/zx-ip-address
```
Your code:  你的业务代码
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

### Notice使用提示
- We don't recommend fork this repository 不推荐fork此仓库
- We recommend using linux's crontab to update ip database推荐使用linux计划任务定期更新数据库

### Auto update 自动更新数据库
```shell
crontab -e
# add line增加一行，每小时更新一次
0 * * * * * cd /var/www/your_project && composer require ritaswc/zx-ip-address
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
