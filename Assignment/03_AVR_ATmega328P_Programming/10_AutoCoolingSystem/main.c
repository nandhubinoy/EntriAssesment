/*
 * 10_AutoCoolingSystem.c
 *
 * Requirements: The system must interface with an LM35 temperature sensor and a
 DC motor. A push-button must be used to toggle the entire system ON and OFF.
 When the system is ON, it should read the temperature and adjust the motor speed
 accordingly. At lower temperatures, the motor should run at a reduced speed, and at
 higher temperatures, the motor should automatically switch to a higher speed. The
 program logic for sensor reading, speed calculation, and motor control must be
 implemented using separate functions.
 *
 * Created: 25-06-2026 13:11:23
 * Author : Nandhu Binoy
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "motorControl.h"
#include "temperature.h"

#define ON_OFF_BUTTON_INPUT	PINB
#define ON_OFF_BUTTON_DDR	DDRB
#define ON_OFF_BUTTON_PIN   PINB0

#define ADC_CHANNEL 0

bool system_is_ON = false;

void SystemSwitchInit()
{
	ON_OFF_BUTTON_DDR	|= (1 << ON_OFF_BUTTON_PIN);
	ON_OFF_BUTTON_INPUT |= (1 << ON_OFF_BUTTON_PIN);
}

uint8_t IsButtonIsPressed()
{
	return (((ON_OFF_BUTTON_INPUT & (1 << ON_OFF_BUTTON_PIN))==0)? 1U: 0U);
}
int main(void)
{
	//Let us assume the Switch is OFF initially
	uint8_t u8PreviousSwitchState = 0U;
	uint16_t u16CurrentTemperature = 0U;
	
	SystemSwitchInit();
	MotorInit();
	ADC_Init();
	
    while (1) 
    {
		if (IsButtonIsPressed() == 1U)
		{
			if(u8PreviousSwitchState == 0U)
			{
				_delay_ms(20);
				if(IsButtonIsPressed() == 1U)
				{
					system_is_ON = !system_is_ON;
				}
			}
		}
		u8PreviousSwitchState = 1;
	
		if (system_is_ON == true)
		{
			uint16_t u16CurrentTemperature = ADC_ReadTemperature(ADC_CHANNEL);
			uint8_t u8targetSpeed = CalculateMotorSpeed(u16CurrentTemperature);
			setMotorSpeed(u8targetSpeed);
			
            // A small delay to prevent the ADC from being polled millions of times a second
            _delay_ms(100);			
		}
		else
		{
			// System is OFF. Ensure the motor is completely stopped.
            stopMotor(); // Assuming you have a function to set PWM to 0 and disable L293D
			
		}
    }
	return 0;
}

