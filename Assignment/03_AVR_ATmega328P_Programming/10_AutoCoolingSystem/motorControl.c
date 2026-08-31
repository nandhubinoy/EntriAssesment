/*
 * motorControl.c
 *
 * Created: 25-06-2026 14:17:12
 *  Author: Nandhu Binoy
 */ 
#include "motorControl.h"
#include "timer_fastPWM.h"

#define MOTOR_ROTATION_IN1	PIND0
#define MOTOR_ROTATION_IN2  PIND1 
#define MOTOR_ROTATION_EN	PIND6

void MotorInit()
{
	InitTimer0forFastPWM();
	// Set PD6 as output, Since MODE 3
	DDRD |= (1 << MOTOR_ROTATION_EN);
	
	// Set 2 control pins for the motor driver as Output
	/* To make the motor spin forward, you must set IN1 to HIGH (5V) and IN2 to LOW (0V) */
	DDRD |= (1 << MOTOR_ROTATION_IN1) | (1 << MOTOR_ROTATION_IN2);
	
		PORTD |= (1 << MOTOR_ROTATION_IN1);  // Set IN1 HIGH
		PORTD &= ~(1 << MOTOR_ROTATION_IN2); // Set IN2 LOW
}

uint8_t CalculateMotorSpeed(uint16_t temperature)
{
	if (temperature > 35) 
	{
       return 255; // 100% speed for very high temp
    } 
    else 
	if (temperature > 29) 
	{
        return 191; // 75% speed
    } 
    else 
	if (temperature >= 25) 
	{
        return 127; // 50% speed
    } 
    else 
	{
        return 64;  // 25% minimum speed if ON, but cold
    }
}

uint8_t setMotorSpeed(uint8_t setValue)
{
	// 1. Set the direction to Forward
	PORTD |= (1 << MOTOR_ROTATION_IN1);  // Set IN1 HIGH
	PORTD &= ~(1 << MOTOR_ROTATION_IN2); // Set IN2 LOW
	
	// 2. Apply the PWM signal to the Enable pin
	OCR0A = setValue; // Assuming you set up Timer0 Mode 3 on pin OC0A
}

void stopMotor(void)
{
	// Brake the motor by setting both direction pins LOW
	PORTD &= ~(1 << MOTOR_ROTATION_IN1);
	PORTD &= ~(1 << MOTOR_ROTATION_IN2);
	
	// Drop PWM to 0
	OCR0A = 0;
}