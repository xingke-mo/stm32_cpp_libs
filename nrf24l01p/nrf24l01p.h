/*
 * work with nRF24L01+ only in DPL mode
 * Not intend to make it compatible with nRF24L01 or nRF2401
 */

#ifndef NRF24L01P_H_
#define NRF24L01P_H_

#include <cstring>
#include "gpio/gpio.h"
#include "spi/spi.h"
#include <stdio.h>

//读RX有效数据,1~32字节
#define R_RX_PLOAD      0x61

//写TX有效数据,1~32字节
#define W_TX_PLOAD      0xA0

//清除TX FIFO寄存器.发射模式下用
#define FLUSH_TX        0xE1

//清除RX FIFO寄存器.接收模式下用
#define FLUSH_RX        0xE2

//重新使用上一包数据,CE为高,数据包被不断发送.
#define REUSE_TX_PL     0xE3

#define R_RX_PL_WID     0x60

//配置寄存器地址;bit0:1接收模式,0发射模式;bit1:电选择;bit2:CRC模式;bit3:CRC使能;
//bit4:中断MAX_RT(达到最大重发次数中断)使能;bit5:中断TX_DS使能;bit6:中断RX_DR使能
#define CONFIG          0x00

//使能自动应答功能  bit0~5,对应通道0~5
#define EN_AA           0x01

//接收地址允许,bit0~5,对应通道0~5
#define EN_RXADDR       0x02

//设置地址宽度(所有数据通道):bit1,0:00,3字节;01,4字节;02,5字节;
#define SETUP_AW        0x03

//建立自动重发;bit3:0,自动重发计数器;bit7:4,自动重发延时 250*x+86us
#define SETUP_RETR      0x04

//RF通道,bit6:0,工作通道频率;
#define RF_CH           0x05

//RF寄存器;bit3:传输速率(0:1Mbps,1:2Mbps);bit2:1,发射功率;bit0:低噪声放大器增益
#define RF_SETUP        0x06

//状态寄存器;bit0:TX FIFO满标志;bit3:1,接收数据通道号(最大:6);bit4,达到最多次重发
#define STATUS          0x07

//bit5:数据发送完成中断;bit6:接收数据中断; 达到最大发送次数中断
#define MAX_TX          0x10

//TX发送完成中断
#define TX_OK           0x20

//接收到数据中断
#define RX_OK           0x40

//发送检测寄存器,bit7:4,数据包丢失计数器;bit3:0,重发计数器
#define OBSERVE_TX      0x08

//载波检测寄存器,bit0,载波检测;
#define CD              0x09

//数据通道0接收地址,最大长度5个字节,低字节在前
#define RX_ADDR_P0      0x0A

//数据通道1接收地址,最大长度5个字节,低字节在前
#define RX_ADDR_P1      0x0B

//数据通道2接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P2      0x0C

//数据通道3接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P3      0x0D

//数据通道4接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P4      0x0E

//数据通道5接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P5      0x0F

//发送地址(低字节在前),ShockBurstTM模式下,RX_ADDR_P0与此地址相等
#define TX_ADDR         0x10

//接收数据通道0有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P0        0x11

//接收数据通道1有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P1        0x12

//接收数据通道2有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P2        0x13

//接收数据通道3有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P3        0x14

//接收数据通道4有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P4        0x15

//接收数据通道5有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P5        0x16

//FIFO状态寄存器;bit0,RX FIFO寄存器空标志;bit1,RX FIFO满标志;bit2,3,保留
#define FIFO_STATUS     0x17

#define DNYPD           0x1C
#define FEATURE         0x1D

extern void delay( u32 );
extern void delayMicroseconds( u32 );

class Nrf24l01p
{
public:
    Nrf24l01p( Spi &spi, Gpio &spi_sck, Gpio &spi_miso, Gpio &spi_mosi,
               Gpio &nrf_irq, Gpio &nrf_csn, Gpio &nrf_ce );
    void init( u8 channel = 0x34 );

    void writeReg( u8 addr, u8 *data, u8 length );
    void writeReg( u8 addr, u8 data );
    void readReg( u8 addr, u8 *data, u8 length );

    u8 send( u8 *dt, u8 length );
    u8 sendFromMaster( u8 *slave_addr, u8 *dt, u8 length );
    u8 sendFromSlave( u8 *dt, u8 length );
    u8 recv( u8 * );

    // len(addr_msbytes) == 4, len(lsbytes) == 5, uniquess required in lsbytes
    void initMaster( u8 *addr_msbytes, u8 *lsbytes );
    void initSlave( u8 *addr );

private:
    Spi &_spi;
    Gpio &_sck;
    Gpio &_miso;
    Gpio &_mosi;

    Gpio &_irq;
    Gpio &_csn;
    Gpio &_ce;

    void setupTx();
    void setupRx();
    void command( u8 );
};

#endif
