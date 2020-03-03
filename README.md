# IPv6 address locations by Zx Inc.
IPv6 address locations by Zx Inc.composer php

##### database updated at 2019-11-30 with 132557 records

## usage
```shell script
composer require ritaswc/zx-ip-address
```
For Example
```php
$tool = new \Ritaswc\ZxIPAddress\IPv6Tool;
$result = $tool->query('240e:e9:8819:0:3::3f9');
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

## Official Web Site
- [IPv6地址查询工具 Nanjing China](http://ip.lsy.cn/)
- [IPv6地址查询工具 Tokyo Japan](http://ip.zxinc.org/)
- [IPv6地址查询工具 Ningbo China](http://ip.ss.zxinc.org//)

## License

ZxIpAddress is licensed under [MIT](https://github.com/ritaswc/zx_ip_address/blob/master/LICENSE).