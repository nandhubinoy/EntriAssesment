/*
 * uart.c
 *
 * Created: 9/1/2026 5:18:42 AM
 *  Author: admin
 */ 
#include "uart.h"
#include <avr/io.h>
void UART_Init()
{
	// 1. Set the Baudrate
	UBRR0L = 103;	// 9600
	UBRR0H = 0;
	// 2. Set Tx and Rx
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
	//3. Set the frame format
	// By default in Asynchronous mode (UMSEL01 = UMSEL00 = 0)
	// Parity Disabled
	// 1 stop bit
	// 8 Bit Character size
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	UCSR0C &= ~(1 << UCSZ02);
}

char UART_Receive(void)
{
	// Wait until data is received
	while (!(UCSR0A & (1 << RXC0)));
	// Return the data
	return UDR0;
}

void UART_Transmit(char data)
{
	/*
	 If UDRE0 is one, the buffer is empty,
	 and therefore ready to be written.
	 */
	while(!(UCSR0A & (1<<UDRE0))); // wait till the condition inside while become false
	
	UDR0 = data;
	
}
void UART_Transmit_String(char *str)
{
	while(*str != '\0')
	{
		UART_Transmit(*str);
		str++;
	}
}

// Memory-efficient function to print numbers without using heavy sprintf()
void UART_PrintNumber(uint8_t num) 
{
	if (num == 0) 
	{
		UART_Transmit('0');
		return;
	}

	char buffer[4]; // Max 3 digits + null terminator
	uint8_t i = 0;

	// Extract digits in reverse order
	while (num > 0) 
	{
		buffer[i++] = (num % 10) + '0';
		num /= 10;
	}

	// Print in correct order
	while (i > 0) 
	{
		UART_Transmit(buffer[--i]);
	}
}

bool UART_Available(void) 
{
	// Check if the Receive Complete (RXC0) flag is set
	return (UCSR0A & (1 << RXC0));
}


