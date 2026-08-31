/*
 * 8_pwmLedBrightness.c
 *
 * Created: 19-06-2026 07:57:18
 * Author : aravi
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define PUSHBUTTON_DDR			DDRB
#define PUSHBUTTON_PORT			PORTB
#define PUSHBUTTON_INPUT_REG	PINB
#define PUSHBUTTON_PIN			PINB0

void InitGPIOPins()
{
	PUSHBUTTON_DDR &= ~(1 << PUSHBUTTON_PIN); // Clears bit 0 of DDRB (Sets PB0 as Input)
	PUSHBUTTON_PORT |= (1 << PUSHBUTTON_PIN); // Enables pull-up on PB0
	
	DDRD |= (1 << DDD6);
	//DDRD |= (1 << DDD5);
}
/* Returns 1U if switch is pressed (active-low), 0U otherwise */
uint8_t GPIO_IsSwitchPressed(void)
{
	return ((PUSHBUTTON_INPUT_REG & (uint8_t)(1U << PUSHBUTTON_PIN)) == 0U) ? 1U : 0U;
}

int main(void)
{
	// Array of duty cycle steps: 0%, 25%, 50%, 75%, 100%
	uint8_t duty_levels[] = {0, 64, 127, 191, 255};
	uint8_t current_step = 0;
	
	InitGPIOPins();
	InitTimer0forFastPWM();
	uint8_t u8ButtonPressed = 0U;
    /* Replace with your application code */
    while (1) 
    {
		if (GPIO_IsSwitchPressed() == 1U)
		{
			if (u8ButtonPressed == 0U)
			{
				_delay_ms(20);
				if(GPIO_IsSwitchPressed() == 1U)
				{
					current_step = (current_step + 1) % 5;
					OCR0A = duty_levels[current_step];
					//OCR0B = duty_levels[current_step];
					u8ButtonPressed = 1U;
				}
			}
		}
		else
		{
			u8ButtonPressed = 0U;
		}
	}
	return 0;
}

