/*
 * motorControl.h
 *
 * Created: 25-06-2026 13:14:47
 *  Author: Nandhu Binoy
 */ 


#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

#include <avr/io.h>
#include "timer_fastPWM.h"

void MotorInit(void);
uint8_t CalculateMotorSpeed(uint16_t);
uint8_t setMotorSpeed(uint8_t);
void stopMotor(void);


#endif /* MOTORCONTROL_H_ */