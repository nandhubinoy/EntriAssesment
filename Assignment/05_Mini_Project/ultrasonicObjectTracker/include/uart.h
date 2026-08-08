#ifndef UART_H
#define UART_H  

#include <stdint.h>

void uart_Init(uint32_t baud);
void uart_SendByte(uint8_t databyte);
void uart_SendString(const char *str);
void uart_SendRawBuffer(const uint8_t *buf, uint8_t len);

#endif // UART_H