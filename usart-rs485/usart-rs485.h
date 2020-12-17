/*
 * usart.h
 *
 *  Created on: May 28, 2013
 *      Author: agu
 */

#ifndef USART_RS485_H_
#define USART_RS485_H_

#include "../usart/usart.h"
#include "../gpio/gpio.h"

#include <cstdlib>

class UsartRs485: public Usart
{
public:
    UsartRs485( u8 sn,
                Gpio &de, Gpio &re,
                uint8_t buff_size = 128,
                uint16_t time_out = 4 );
    virtual ~UsartRs485();

    void init( uint32_t baudrate = 9600,
               uint16_t word_length = USART_WordLength_8b,
               uint16_t stop_bits = USART_StopBits_1,
               uint16_t parity = USART_Parity_No,
               uint16_t mode = USART_Mode_Rx | USART_Mode_Tx,
               uint16_t hardware_flow_control = USART_HardwareFlowControl_None );

    void flush();

protected:
    void onTXE();

private:
    Gpio &_de;
    Gpio &_re;
    uint16_t _time_out;
};

#endif /* USART_H_ */
