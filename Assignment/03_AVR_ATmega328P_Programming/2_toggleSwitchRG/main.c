/*
 * 2_toggleSwitchRG.c
 *
 * Created: 07-06-2026 12:26:47
 * Author : Nandhu Binoy
 
 Requirements: The system must interface with a Red LED, a Green LED, and a push-button switch. 
 When the switch is pressed, the program must toggle the current active LED state. If the Red LED is currently ON, 
 it must be turned OFF while the Green LED is turned ON. Conversely, if the Green LED is currently ON, 
 it must be turned OFF while the Red LED is turned ON. 
 Each individual press of the switch should trigger exactly one transition between the two LEDs.

 */ 

#define F_CPU 16000000UL

#include <stdbool.h>
#include <util/delay.h>
#include <stdint.h>

#include "gpio.h"
/* ---------------------------------------------------------------
 * Types
 * MISRA Rule 6.3: Use typedef names for numeric types.
 * --------------------------------------------------------------- */
typedef enum
{
	LED_STATE_RED = 0U,
	LED_STATE_GREEN = 1U	
}LedState_t;

/* ---------------------------------------------------------------
 * Static (file-scope) state
 * MISRA Rule 8.7: Objects that are only used within one translation
 * unit shall have internal linkage.
 * --------------------------------------------------------------- */
static LedState_t s_currentLedState = LED_STATE_RED;

static void HandleSwitchPress(void);

int main(void)
{
	GPIO_LED_PinInit();
	GPIO_Switch_PinInit();
	uint8_t u8SwitchWasPressed = 0U;  /* Tracks previous switch state */
	while(1)
	{
		if(GPIO_IsSwitchPressed() == 1U)
		{
			if(u8SwitchWasPressed == 0U)
			{
				_delay_ms(20);
				if(GPIO_IsSwitchPressed() == 1U)
				{
					HandleSwitchPress();
					u8SwitchWasPressed = 1U;
				}
			}
		}
		else
		{
			u8SwitchWasPressed = 0U;
		}
	}
	return 0;
}

/* ---------------------------------------------------------------
 * HandleSwitchPress
 * Toggles LED state machine on each confirmed switch press.
 * --------------------------------------------------------------- */
static void HandleSwitchPress(void)
{
    if (s_currentLedState == LED_STATE_RED)
    {
        GPIO_SetGreenLed();
        s_currentLedState = LED_STATE_GREEN;
    }
    else
    {
        GPIO_SetRedLed();
        s_currentLedState = LED_STATE_RED;
    }
}
