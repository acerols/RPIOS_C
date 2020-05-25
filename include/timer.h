#ifndef _TIMER_H
#define _TIMER_H

#include "typedef.h"

#define CORE0_TIMER_IRQCNTL ((volatile uint32_t *)(0x40000040))
#define CORE0_IRQ_SOURCE    CORE0_INTERRUPT_SOURCE

void set_timer(void);
void init_timer(uint32_t usec);

#endif