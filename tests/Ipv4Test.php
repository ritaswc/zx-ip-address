<?php
namespace App\tests;

use PHPUnit\Framework\TestCase;
use Ritaswc\ZxIPAddress\IPv4Tool;

class Ipv4Test extends TestCase
{
    public function testIpv4Total()
    {
        $this->assertGreaterThan(0, IPv4Tool::total());
    }

    public function testQuery()
    {
        $arr = IPv4Tool::query('255.255.255.255');
        $this->assertEquals('255.255.255.0', $arr['start']);
        $this->assertEquals('255.255.255.255', $arr['end']);
        $this->assertEquals('纯真网络', $arr['addr'][0]);
    }
}