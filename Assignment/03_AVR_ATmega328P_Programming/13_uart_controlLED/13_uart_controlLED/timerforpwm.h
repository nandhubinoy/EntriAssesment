/*
 * timerforpwm.h
 *
 * Created: 9/1/2026 5:19:27 AM
 *  Author: Nandhu
 */ 


#ifndef TIMERFORPWM_H_
#define TIMERFORPWM_H_

#include <avr/io.h>
void phaseCorrectPWM_Init();
void PWM_SetBrightness(uint8_t percentage) ;



#endif /* TIMERFORPWM_H_ */