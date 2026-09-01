/*
 * uart.h
 *
 * Created: 9/1/2026 5:18:22 AM
 *  Author: Nandhu
 */ 


#ifndef UART_H_
#define UART_H_
#include <avr/io.h>
#include <stdio.h>
#include  <stdint.h>
#include <stdbool.h>

void UART_Init();
char UART_Receive(void);
void UART_Transmit(char data);
void UART_Transmit_String(char *str);
void UART_PrintNumber(uint8_t num) ;
bool UART_Available(void) ;


#endif /* UART_H_ */