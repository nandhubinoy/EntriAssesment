/*
 * temperature.c
 *
 * Created: 25-06-2026 14:00:30
 *  Author: Nandhu Binoy
 */ 


#include <avr/io.h>
#include "temperature.h"

void ADC_Init()
{
	// Select Vref as Internal 1.1V
	//ADMUX &= ~((1 << REFS1) | (1 << REFS0));
	ADMUX |= (1 << REFS1) | (1 << REFS0);
	
	// Enable ADC, SET Prescalar 128
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
	// Left Adjust (By default)
	//ADMUX &= ~(1 << ADLAR)
}

uint16_t ADC_ReadTemperature(uint16_t ADCchannel)
{
	// Confine the ADC Channel value not to cross 15
	ADCchannel &= 0x0F;
	
	// MASK AND SET: Clear the bottom 4 bits (0xF0), then set the new channel
	ADMUX = (ADMUX & 0xF0) | ADCchannel;
	
	ADCSRA |= (1 << ADSC); // Start Conversion
	
	while(ADCSRA & (1 << ADSC))
	{
		// Do Nothing, Wait till complete conversion
	}
	return ADC;
}