#include <avr/io.h>
#include <stdint.h>

// Requirements:
// 1. Potentiometer on ADC Channel 0
// 2. Servo on OC1A (PORTB Pin 1)
// 3. Timer1 16-bit Phase Correct PWM (50Hz)

// Math for Timer1 Phase Correct PWM:
// f_PWM = F_CPU / (2 * Prescaler * TOP)
// 50Hz = 16,000,000 / (2 * 8 * TOP)
// TOP = 20,000
// At Prescaler 8, Timer clock is 2MHz. Each tick is 0.5 microseconds.
#define PWM_TOP 20000

// Servo Pulse Widths:
// Standard servos require a 1ms to 2ms pulse width for 0-180 degrees.
// 1ms = 2000 ticks (2000 * 0.5us = 1000us = 1ms)
// 2ms = 4000 ticks (4000 * 0.5us = 2000us = 2ms)
// Note: Some SG90 servos prefer 0.5ms to 2.4ms (1000 to 4800 ticks) for a full 180 sweep.
#define SERVO_MIN_TICKS 500 //2000
#define SERVO_MAX_TICKS 2400 //4800

void ADC_Init(void) {
// Set Reference Voltage to AVCC (5V on Uno)
ADMUX = (1 << REFS0);

// Enable ADC and set Prescaler to 128 (16MHz/128 = 125kHz, ideal for 10-bit ADC)
ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);


}

uint16_t ADC_Read(uint8_t channel) {
// Ensure channel is 0-7, mask out other bits, and apply to ADMUX
ADMUX = (ADMUX & 0xF0) | (channel & 0x07);

// Start Single Conversion
ADCSRA |= (1 << ADSC);

// Wait for conversion to complete (ADSC bit becomes 0)
while (ADCSRA & (1 << ADSC));

// Return the 10-bit ADC result
return ADC;


}

void Timer1_Init(void) {
// Set OC1A (PB1) as Output
DDRB |= (1 << PB1);

// Configure Timer1 for 16-bit Phase Correct PWM (Mode 10)
// Mode 10 uses ICR1 as the TOP value.
// TCCR1A: COM1A1=1, COM1A0=0 (Clear OC1A on up-counting, set on down-counting)
// TCCR1A: WGM11=1, WGM10=0
TCCR1A = (1 << COM1A1) | (1 << WGM11);

// TCCR1B: WGM13=1, WGM12=0
// TCCR1B: CS11=1 (Prescaler = 8)
TCCR1B = (1 << WGM13) | (1 << CS11);

// Set TOP value for 50Hz frequency
ICR1 = PWM_TOP;


}

// Function to map ADC value (0-1023) to Servo Pulse Width Ticks
uint16_t Map_ADC_to_Servo(uint16_t adc_val) 
{
    // Standard mapping formula: (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min
    // Using 32-bit math to prevent overflow during multiplication
    uint32_t mapped = SERVO_MIN_TICKS + ((uint32_t)adc_val * (SERVO_MAX_TICKS - SERVO_MIN_TICKS)) / 1023;
    return (uint16_t)mapped;
}

int main(void) 
{
    // Hardware Initialization
    ADC_Init();
    Timer1_Init();

    uint16_t pot_value = 0;

    while (1) 
    {
        // Read Potentiometer from Channel 0
        pot_value = ADC_Read(0);
        
        // Map 10-bit ADC to required PWM pulse width and update Timer Compare Register
        OCR1A = Map_ADC_to_Servo(pot_value);
        
        // No explicit delay needed; Timer1 handles the 50Hz output autonomously in hardware!
    }

return 0;


}