/*
 * 9_motorSpeedControl.c
 *
 * Created: 26-06-2026 08:05:52
 * Author : Nandhu Binoy
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define MOTOR_ROTATION_IN1	PIND0
#define MOTOR_ROTATION_IN2  PIND1
#define MOTOR_ROTATION_EN	PIND6

void GPIOPinInit()
{
	DDRD |= (1 << DDD0) | (1 << DDD1) | (1 << DDD6);
}

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
	
	OCR0A = 61;
}

int main(void)
{
	GPIOPinInit();
	InitTimer0forFastPWM();
    /* Replace with your application code */
    while (1) 
    {
		PORTD |= (1 << MOTOR_ROTATION_IN1);
		PORTD &= ~(1 << MOTOR_ROTATION_IN2);
		_delay_ms(1000);
    }
	return 0;
}

