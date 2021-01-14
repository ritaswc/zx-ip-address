<?php

namespace App\tests;

use PHPUnit\Framework\TestCase;
use Ritaswc\ZxIPAddress\IPv6Tool;
use Ritaswc\ZxIPAddress\RuntimeException;

class IPv6Test extends TestCase
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
        try {
            IPv6Tool::query('2409::e7ef::76c9');
        } catch (\Exception $exception) {
            $this->assertEquals(RuntimeException::class, get_class($exception));
        }
    }

    public function testValidator()
    {
        $this->assertEquals(false, IPv6Tool::isValidAddress('1.1.1.1'));
        $this->assertEquals(false, IPv6Tool::isValidAddress('2.2.2.2'));
        $this->assertEquals(false, IPv6Tool::isValidAddress('0.0.0.0'));
        $this->assertEquals(false, IPv6Tool::isValidAddress('1.323.32.1'));
        $this->assertEquals(true, IPv6Tool::isValidAddress('::1'));
        $this->assertEquals(true, IPv6Tool::isValidAddress('2409:8954:48f0:3a01:b12b:5ea9:e7ef:76c9'));
        $this->assertEquals(false, IPv6Tool::isValidAddress('2409:8954:48f0:3a01:b12b:5ea9::e7ef:76c9'));
        $this->assertEquals(false, IPv6Tool::isValidAddress('2409::e7ef::76c9'));
        $this->assertEquals(true, IPv6Tool::isValidAddress('2409:8954::1'));
        $this->assertEquals(true, IPv6Tool::isValidAddress('2409:8954::'));
    }
}