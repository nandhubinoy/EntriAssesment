/*
 * gpio.c
 *
 * Created: 07-06-2026 12:36:13
 *  Author: Nandhu Binoy
 *
 * GPIO Driver Implementation
 */ 

#include "gpio.h"

void GPIO_LED_PinInit(void)
{
	/* Set PD5 (Green) and PD6 (Red) as outputs */
	GREEN_LED_DDR |= (uint8_t)(1U << GREEN_LED_PIN);
	RED_LED_DDR	  |= (uint8_t)(1U << RED_LED_PIN);
	/* Initial state: Red ON, Green OFF */
	GREEN_LED_PORT&= (uint8_t)(~(1U << GREEN_LED_PIN));
	RED_LED_PORT  |= (uint8_t)(1U << RED_LED_PIN);
}

void GPIO_Switch_PinInit(void)
{
	TOGGLE_SWITCH_DDR &= (uint8_t)(~(1 << TOGGLE_SWITCH_PIN));
	
	/* Enable internal pull-up resistor */
    //TOGGLE_SWITCH_PORT |= (uint8_t)(1U << TOGGLE_SWITCH_PIN);
}

void GPIO_SetGreenLed(void)
{
	GREEN_LED_PORT	|= (uint8_t)(1U << GREEN_LED_PIN);
	RED_LED_PORT	&= (uint8_t)(~(1U << RED_LED_PIN));
}

void GPIO_SetRedLed(void)
{
	GREEN_LED_PORT	&= (uint8_t)(~(1U << GREEN_LED_PIN));
	RED_LED_PORT	|= (uint8_t)(1U << RED_LED_PIN);	
}

/* Returns 1U if switch is pressed (active-low), 0U otherwise */
uint8_t GPIO_IsSwitchPressed(void)
{
	return ((TOGGLE_SWITCH_INPUT & (uint8_t)(1U << TOGGLE_SWITCH_PIN)) == 1U) ? 1U : 0U;
}