/*
 * 1_toggleLED.c
 *
 * Created: 07-06-2026 11:45:55
 * Author : Nandhu Binoy
 REQUIREMENTS:
 The LED must be interfaced with PORTD Pin 5. Upon system start or reset, the 
 LED must immediately turn ON and remain in that state for exactly 3 seconds. 
 After the ON period, the LED must turn OFF for a duration of exactly 5 seconds. 
 The program must be designed to continuously loop this 3-second ON and 5-second OFF sequence.
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define LED_PORT PORTD
#define LED_DDR	 DDRD
#define LED_PIN	 5

void GPIO_PinInit()
{
	LED_DDR |= (1<<LED_PIN);
	LED_PORT &= ~(1<<LED_PIN);
}

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		PORTD |= (1<<LED_PIN);
		_delay_ms(3000);
		LED_PORT &= ~(1<<LED_PIN);
		_delay_ms(5000);
    }
	return 0;
}

