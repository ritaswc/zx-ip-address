<?php
namespace App\tests;

use PHPUnit\Framework\TestCase;
use Ritaswc\ZxIPAddress\IPv6Tool;

class Ipv6Test extends TestCase
{
    public function testIpv4Total()
    {
        $this->assertGreaterThan(0, IPv6Tool::total());
    }

    public function testQuery()
    {
        $arr = IPv6Tool::query('FFFF:FFFF:FFFF:FFFF::');
        $this->assertEquals('ffff:ffff:ffff:fff0::', $arr['start']);
        $this->assertEquals('ffff:ffff:ffff:ffff::', $arr['end']);
        $this->assertEquals('ZX公网IPv6库', $arr['addr'][0]);
    }
}