/*
 * timerforpwm.c
 *
 * Created: 9/1/2026 5:20:10 AM
 *  Author: Nandhu
 */ 
#include "timerforpwm.h"
void phaseCorrectPWM_Init()
{
	
	// Set PB1 (Digital Pin 9) as output for OC1A
	DDRB |= (1 << PINB1);
	
	// Timer1 Configuration: Phase Correct PWM, TOP = ICR1 (Mode 10)
	// COM1A1 = 1: Non-inverted PWM on OC1A
	// WGM11 = 1: Part of Mode 10 setup
	TCCR1A = (1 << COM1A1) | (1 << WGM11); // Clear OC1A/OC1B on compare match when up-counting. 
										   // Set OC1A/OC1B on compare match when down counting
	TCCR1B |= (1 << WGM13);
	
	/*
		Frequency = (fclk / (2 x N x ICR1))
	*/
	// WGM13 = 1: Part of Mode 10 setup
	// CS11 = 1, CS10 = 1: Prescaler 64
	TCCR1B = (1 << WGM13) | (1 << CS11) | (1 << CS10);

	// Set TOP value to exactly 100.
	// This allows us to map 0-100% brightness directly to 0-100 in the compare register!
	ICR1 = 100;

	// Start with LED off
	OCR1A = 0;	
}
void PWM_SetBrightness(uint8_t percentage) 
{
	// Safety check: Clamp value to max 100
	if (percentage > 100) 
	{
		percentage = 100;
	}
	// Update the duty cycle
	OCR1A = percentage;
}
