#ifndef _TIMER_H
#define _TIMER_H

#include "gpio.h"

#define PBASE       MMIO_BASE

#define TIMER_CS        ((volatile unsigned int *)(PBASE+0x00003000))
#define TIMER_CLO       ((volatile unsigned int *)(PBASE+0x00003004))
#define TIMER_CHI       ((volatile unsigned int *)(PBASE+0x00003008))
#define TIMER_C0        ((volatile unsigned int *)(PBASE+0x0000300C))
#define TIMER_C1        ((volatile unsigned int *)(PBASE+0x00003010))
#define TIMER_C2        ((volatile unsigned int *)(PBASE+0x00003014))
#define TIMER_C3        ((volatile unsigned int *)(PBASE+0x00003018))

#define TIMER_CS_M0	(1 << 0)
#define TIMER_CS_M1	(1 << 1)
#define TIMER_CS_M2	(1 << 2)
#define TIMER_CS_M3	(1 << 3)

void wait_cycles(unsigned int n);
void wait_msec(unsigned int n);
unsigned long get_system_timer();
void wait_msec_st(unsigned int n);

#endif