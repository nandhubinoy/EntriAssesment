#include "adc.h"
#include <avr/io.h>

void adc_Init(void)
{
    // Set the reference voltage to AVcc (5V) and select ADC channel 0 (PC0)
    ADMUX = (uint8_t)(1 << REFS0); // AVcc with external capacitor at AREF pin

    // Enable the ADC and set the prescaler to 128 for 16MHz clock
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}
uint16_t adc_Read(uint8_t channel)
{
    // Select the ADC channel (0-7)
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    // Start the conversion
    ADCSRA |= (1 << ADSC);

    // Wait for the conversion to complete
    while (ADCSRA & (1 << ADSC));

    // Read the ADC value (10-bit result)
    uint16_t adcValue = ADC;

    return adcValue;
}