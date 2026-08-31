/*
 * timer_fastPWM.c
 *
 * Created: 19-06-2026 11:08:26
 *  Author: Nandhu Binoy
 */ 
#include "timer_fastPWM.h"
void InitTimer0forFastPWM()
{
	// Compare Output Mode, Fast PWM Mode
	TCCR0A |= (1<<COM0A1);
	TCCR0A &= ~(1<<COM0A0);
	
	// Waveform generation, 
	// Select Mode 3, for variable duty cycle
	TCCR0B &= ~(1<<WGM02); 
	TCCR0A |= (1<<WGM00) | (1<<WGM01);
	
	// Prescalar = 64
	TCCR0B &= ~(1<<CS02);
	TCCR0B |=  (1<<CS01) | (1<<CS00); 
	
	OCR0A = 0;
}