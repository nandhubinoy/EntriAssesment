/*
 * 13_uart_controlLED.c
 *
 * Created: 9/1/2026 5:12:07 AM
 * Author : Nandhu
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include "uart.h"
#include "timerforpwm.h"

// Helper function to check if a string contains only numbers
bool IsNumeric(const char* str) 
{
	if (*str == '\0') return false;
	for (uint8_t i = 0; str[i] != '\0'; i++) 
	{
		if (str[i] < '0' || str[i] > '9') 
		{
			return false;
		}
	}
	return true;
}

// Parses the completed command string and controls the hardware
void ProcessCommand(const char* cmd) 
{
	if (strcmp(cmd, "ON") == 0) 
	{
		PWM_SetBrightness(100);
		UART_Transmit_String("LED is now ON\r\n");
	}
	else if (strcmp(cmd, "OFF") == 0) 
	{
		PWM_SetBrightness(0);
		UART_Transmit_String("LED is now OFF\r\n");
	}
	else if (IsNumeric(cmd)) 
	{
		int val = atoi(cmd); // Convert string to integer
		if (val >= 0 && val <= 100) 
		{
			PWM_SetBrightness((uint8_t)val);
			UART_Transmit_String("Brightness set to ");
			UART_PrintNumber((uint8_t)val);
			UART_Transmit_String("%\r\n");
		} 
		else 
		{
			UART_Transmit_String("Error: Brightness must be 0-100\r\n");
		}
	}
	else 
	{
		UART_Transmit_String("Invalid command. Send 'ON', 'OFF', or '0'-'100'\r\n");
	}
}

int main(void)
{
	phaseCorrectPWM_Init();
	UART_Init();
	UART_Transmit_String("\r\n--- UART Based LED Brightness Controller ---\r\n");
	
	char rxBuffer[16];
	uint8_t rxIndex = 0;
    while (1) 
    {
		if(UART_Available())
		{
			char c = UART_Receive();
			
			// Check if character is "Enter" key
			if (c == '\n' || c == '\r')
			{
				if(rxIndex > 0)
				{
					rxBuffer[rxIndex] = '\0';
					ProcessCommand(rxBuffer);
					rxIndex = 0;
				}
			}
			else
			if (rxIndex < sizeof(rxBuffer) -1)
			{
				// only accept standard text
				if (c >= ' ' && c <= '~')
				{
					rxBuffer[rxIndex] = c;
					rxIndex++;
				}
			}
		}
    }
	return 0;
}

