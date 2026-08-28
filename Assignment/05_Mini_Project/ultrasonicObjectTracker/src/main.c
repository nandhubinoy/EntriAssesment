#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "uart.h"
#include "timer.h"
#include "adc.h"
#include "tracker.h"

/* HC-SR04 Ultrasonic Sensor 
Trigger pin: PD2 = Arduino Pin PD2
(echo uses ICP1 = PB0 = PD8)
*/
#define TRIGGER_DDR  DDRD
#define TRIGGER_PORT PORTD
#define TRIGGER_PIN  PD2

#define SWEEP_MIN_DEG  15U
#define SWEEP_MAX_DEG  165U
#define SWEEP_STEP_DEG 5U

#define ECHO_TIMEOUT_POLLS 30000UL /* bounds the wait time for missing echo signals */

#define TELEMETRY_SYNC_BYTE 0xAAU

/* Timer1 tick = prescaler(8) / F_CPU = 0.5us @ 16MHz.
 * range_mm = (ticks * 0.5us) * speed_of_sound(343 m/s) / 2
 *          ≈ ticks * 0.0857 mm/tick -> scaled integer math below. */
 static int16_t range_mm_from_ticks(uint16_t ticks)
 {
    uint32_t mm = ((uint32_t)ticks * 857UL) / 10000UL; /* ticks * 0.0857 mm/tick */
    if(mm > 4000UL)
    {
        mm = 4000UL; /* cap at 4 meters 
                        HC-SR04's ~400cm max range*/
    }
    return (int16_t)mm;
 }

static void triggerPulse(void)
{
    TRIGGER_PORT &= (uint8_t)~(1 << TRIGGER_PIN);
    _delay_us(2);
    TRIGGER_PORT |= (uint8_t)(1 << TRIGGER_PIN);
    _delay_us(10); /* HC-SR04 datasheet: >=10us trigger pulse */
    TRIGGER_PORT &= (uint8_t)~(1 << TRIGGER_PIN);
}

static uint8_t checksum8(const uint8_t *buf, uint8_t len)
{
    uint8_t sum = 0;
    for(uint8_t i = 0; i < len; i++)
    {
        sum ^= buf[i];
    }
    return sum;
}

/* Packet layout (FR-9): SYNC, ID, RANGE_LO, BEARING,
                            VEL_LO, VEL_HI, CONFIDENCE -- 9 bytes*/
static void send_telemetry(const track_t *t, uint16_t aux_adc)
{
/*    
    uint8_t pkt[9];

    pkt[0] = TELEMETRY_SYNC_BYTE;
    pkt[1] = t->id;
    pkt[2] = (uint8_t)(t->rangeInMillimetres & 0xFF);
    pkt[3] = (uint8_t)((t->rangeInMillimetres >> 8) & 0xFF);
    pkt[4] = t->bearingInDegrees;
    pkt[5] = (uint8_t)(t->velocityInMillimetresPerSweep & 0xFF);
    pkt[6] = (uint8_t)((t->velocityInMillimetresPerSweep >> 8) & 0xFF);
        // confidence placeholder: inverse of miss_count, refine in design.md 
    pkt[7] = (uint8_t)(100U - (t->missedSweeps * 25U));
    pkt[8] = checksum8(pkt, 8);

    uart_SendRawBuffer(pkt, sizeof(pkt));

    // Aux ADC channel reported as plain text for now (FR-10 demo) --
    // a binary field can be folded into the packet once format is finalized. 
    
    uart_SendString("AUX:");
    uart_SendByte((uint8_t)('0' + (aux_adc / 100) % 10));
    uart_SendByte((uint8_t)('0' + (aux_adc / 10) % 10));
    uart_SendByte((uint8_t)('0' + aux_adc % 10));
    uart_SendString("\r\n");  
*/
    char out_buf[80];
    // Format all telemetry fields into human-readable text
    snprintf(out_buf, sizeof(out_buf),
             "ID:%u | Dist:%4dmm | Angle:%3u deg | Vel:%4d | Conf:%3u%% | AUX:%u\r\n",
             t->id,
             t->rangeInMillimetres,
             t->bearingInDegrees,
             t->velocityInMillimetresPerSweep,
             (unsigned int)(100U - (t->missedSweeps * 25U)),
             aux_adc);

    uart_SendString(out_buf);         
     
}

int main()
{
    TRIGGER_DDR |= (uint8_t)(1 << TRIGGER_PIN);

    uart_Init(9600);

    timer1_InitforServoPWM();
    timer1_InitEchoCapture();
    adc_Init();
    tracker_init();

    sei(); // Enable global interrupts for input capture ISR

    uart_SendString("ultrasonicObjectTracker boot OK\r\n");

    bool sweeping_up = true;
    uint8_t angle = SWEEP_MIN_DEG;

    while (1)
    {
        timer1_setServoAngle(angle);
        _delay_ms(50);

        triggerPulse();

        bool got_echo = false;
        uint16_t ticks =  0;
        for (uint32_t i = 0; i < ECHO_TIMEOUT_POLLS && !got_echo; i++)
        {
            got_echo = timer1_getEchoTicks(&ticks);
        }

        if(got_echo)
        {
            int16_t range_in_mm = range_mm_from_ticks(ticks);
            /* FR-5: discard out-of-window readings as noise before tracking */
            if(range_in_mm >= 20 && range_in_mm <= 4000)
            {                      
                const track_t *t = tracker_process(angle, true, range_in_mm);
                uint16_t aux = adc_Read(0);
                if(t != NULL)
                {
                    send_telemetry(t, aux);
                }
            }
        }

        if (sweeping_up)
        {
            if(angle + SWEEP_STEP_DEG > SWEEP_MAX_DEG)
            {
                sweeping_up  = false;
                tracker_end_of_sweep(); /* FR-8: age out tracks missed this pass */
            }
            else
            {
                angle = (uint8_t)(angle + SWEEP_STEP_DEG);
            }
        }
        else
        {
            if (angle < SWEEP_MIN_DEG + SWEEP_STEP_DEG)
            {
                sweeping_up  = true;
                tracker_end_of_sweep();                
            }
            else
            {
                angle = (uint8_t)(angle - SWEEP_STEP_DEG);
            }
            
        }
        
        
    }
    
    return 0;
}
