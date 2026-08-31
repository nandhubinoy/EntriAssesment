/*
 * gpio.h
 *
 * Created: 07-06-2026 12:36:54
 *  Author: nandhu binoy
 */ 


#ifndef GPIO_H_
#define GPIO_H_
#include <avr/io.h>
#include <stdint.h>

/* --- Green LED (PD5) --- */
#define GREEN_LED_PORT   PORTD
#define GREEN_LED_DDR	 DDRD
#define GREEN_LED_PIN	 5U

/* --- Red LED (PD6) --- */
#define RED_LED_PORT	PORTD
#define RED_LED_DDR		DDRD
#define RED_LED_PIN		6U

/* --- Toggle Switch (PB0, active-low with internal pull-up) --- */
#define TOGGLE_SWITCH_PORT	PORTB
#define TOGGLE_SWITCH_DDR	DDRB
#define TOGGLE_SWITCH_INPUT PINB
#define TOGGLE_SWITCH_PIN	0U

/* --- Public API --- */
void GPIO_LED_PinInit(void);
void GPIO_Switch_PinInit(void);
void GPIO_SetGreenLed(void);
void GPIO_SetRedLed(void);
uint8_t GPIO_IsSwitchPressed(void);

#endif /* GPIO_H_ */