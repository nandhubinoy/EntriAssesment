#include "uart.h"
#include <avr/io.h>

void uart_Init(uint32_t baud)
{

    uint16_t ubrr_value = (F_CPU / (16 * baud)) - 1;
    // Set baud rate to 9600 for 16MHz clock
    UBRR0H = (uint8_t)(ubrr_value >> 8);
    UBRR0L = (uint8_t)(ubrr_value & 0xFF);

    UCSR0B |= (1<<TXEN0); // Enable UART Transmission
    UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00); // Set frame format: 8 data bits
    UCSR0C &= ~(1<<USBS0); // Set 1 stop bit
}

void uart_SendByte(uint8_t databyte)
{
    while(!(UCSR0A & (1 << UDRE0)))
    {

    }
    UDR0 = databyte;
}

void uart_SendString(const char *str)
{
    while(*str != '\0')
    {
        uart_SendByte((uint8_t)*str);
        str++;
    }
}

void uart_SendRawBuffer(const uint8_t *buf, uint8_t len)
{
    for(uint8_t i = 0; i < len; i++)
    {
        uart_SendByte(buf[i]);
    }
}
