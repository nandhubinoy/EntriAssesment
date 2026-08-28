#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void adc_Init(void);
uint16_t adc_Read(uint8_t channel);

#endif // ADC_H