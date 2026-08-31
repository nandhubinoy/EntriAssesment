/*
 * temperature.h
 *
 * Created: 25-06-2026 13:14:11
 *  Author: Nandhu Binoy
 */ 


#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_ 

#include <avr/io.h>


void ADC_Init();
uint16_t ADC_ReadTemperature(uint16_t channel);


#endif /* TEMPERATURE_H_ */