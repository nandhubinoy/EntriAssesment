#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stdbool.h>

void timer1_InitforServoPWM();
void timer1_setServoAngle(uint8_t angleInDegrees);
void timer1_InitEchoCapture(void);
bool timer1_getEchoTicks(uint16_t *ticksOut);

#endif // TIMER_H