<?php

namespace App\tests;

use PHPUnit\Framework\TestCase;
use Ritaswc\ZxIPAddress\IPv4Tool;
use Ritaswc\ZxIPAddress\RuntimeException;

class IPv4Test extends TestCase
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
        try {
            IPv4Tool::query('255.255.255.257');
        } catch (\Exception $exception) {
            $this->assertEquals(RuntimeException::class, get_class($exception));
        }
    }

    public function testValidator()
    {
        $this->assertEquals(true, IPv4Tool::isValidAddress('1.1.1.1'));
        $this->assertEquals(true, IPv4Tool::isValidAddress('2.2.2.2'));
        $this->assertEquals(true, IPv4Tool::isValidAddress('0.0.0.0'));
        $this->assertEquals(false, IPv4Tool::isValidAddress('3.2.4'));
        $this->assertEquals(false, IPv4Tool::isValidAddress('3.2.4.5.3'));
        $this->assertEquals(false, IPv4Tool::isValidAddress('1.256.32.1'));
        $this->assertEquals(false, IPv4Tool::isValidAddress('::1'));
    }
}