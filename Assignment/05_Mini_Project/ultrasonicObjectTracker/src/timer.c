#include <timer.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

/*
 * Design note (see docs/SRS.md open design decisions):
 * Fast PWM mode 14 uses ICR1 as TOP, but ICR1 is also the only register the
 * Input Capture Unit can write to. Since this project needs BOTH servo PWM
 * and echo input capture on Timer1, we use Fast PWM mode 15 instead:
 *   - TOP is OCR1A (sets the 50Hz servo frame period)
 *   - PWM duty output is on OC1B (servo signal -> Arduino pin D10, not D9)
 *   - ICR1 is left free for the Input Capture Unit (echo pulse on D8/ICP1)
 */

#define SERVO_PWM_TOP      39999U /* 16MHz / 8 prescaler / 50Hz - 1 */
#define SERVO_PULSE_MIN    2000U  /* ~1.0ms pulse (0 deg) */
#define SERVO_PULSE_MAX    4000U  /* ~2.0ms pulse (180 deg) */
#define SERVO_ANGLE_MAX    180U


static volatile uint16_t capture_start_ticks = 0;
static volatile uint16_t capture_width_ticks = 0;
static volatile bool     capture_rising_edge = true;
static volatile bool     capture_ready = false;


void timer1_InitforServoPWM()
{
    // FastPWM WGM13:10 = 1111 (mode 15)
    TCCR1A = (uint8_t)(1 << WGM11) | (1 << WGM10);
    TCCR1B = (uint8_t)(1 << WGM13) | (1 << WGM12);

    // Set prescaler to 8 (16MHz / 8 = 2MHz timer clock)
    TCCR1B |= (1 << CS11) | (0 << CS10) | (0 << CS12);

    // In FastPWM mode 15, OCR1A is TOP and OCR1B is the compare match for the PWM output.
    // Making COM1B1:0 = 10 (non-inverting mode) will set OC1B high at BOTTOM and low at OCR1B.
    // When compare match occurs, the output will go low, creating a PWM signal with a duty cycle determined by OCR1B.
    TCCR1A |= (1 << COM1B1);
    TCCR1A &= ~(1 << COM1B0); // Clear COM1B0 for non-inverting mode

    OCR1A = SERVO_PWM_TOP;// Set TOP for 50Hz PWM frame period
    OCR1B = SERVO_PULSE_MIN; // Set initial pulse width (0 deg)

    // Set ICR1 as input capture register for echo pulse measurement
    // (no need to set ICR1 here, it will be set by the Input Capture Unit when a rising edge is detected)

    //Set OC1B (D10) as output for servo PWM signal
    DDRB |= (1 << PB2); // Set PB2 (D10) as output
}
void timer1_setServoAngle(uint8_t angleInDegrees)
{
    if (angleInDegrees > SERVO_ANGLE_MAX) 
    {
        angleInDegrees = SERVO_ANGLE_MAX; // Clamp to max angle
    }

    uint32_t span = (uint32_t)(SERVO_PULSE_MAX - SERVO_PULSE_MIN);
    uint32_t pulseWidth = (uint16_t)(SERVO_PULSE_MIN + 
                            ((span * angleInDegrees) / SERVO_ANGLE_MAX));

    OCR1B = (uint16_t)pulseWidth; // Update OCR1B for new pulse width

}
void timer1_InitEchoCapture(void)
{
    DDRB &= ~(1 << PB0); // Set PB0 (D8) as input for echo signal
    
    TCCR1B |= (uint8_t)(1 << ICNC1) | (1 << ICES1); // Enable noise canceler and capture on rising edge
    capture_rising_edge = true; // Start with rising edge detection
    
    //Enable Input Capture Interrupt
    TIMSK1 |= (uint8_t)(1 << ICIE1);
}
bool timer1_getEchoTicks(uint16_t *ticksOut)
{
        bool ready;
    uint16_t width;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        ready = capture_ready;
        width = capture_width_ticks;
        capture_ready = false;
    }

    if (ready) {
        *ticksOut = width;
    }
    return ready;
}

ISR(TIMER1_CAPT_vect)
{
    if (capture_rising_edge) {
        capture_start_ticks = ICR1;
        TCCR1B &= (uint8_t)~(1 << ICES1); /* switch to capture falling edge next */
        capture_rising_edge = false;
    } else {
        /* Handles the common case; single-cycle timer wraparound during one
         * echo pulse is not expected at this pulse-width scale but is a
         * known simplification -- see docs/design.md limitations section. */
        capture_width_ticks = (uint16_t)(ICR1 - capture_start_ticks);
        capture_ready = true;
        TCCR1B |= (uint8_t)(1 << ICES1); /* back to capturing rising edge */
        capture_rising_edge = true;
    }
}