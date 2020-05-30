#include "typedef.h"
#include "exec.h"
#include "timer.h"

// Memory-Mapped I/O output
static inline void mmio_write(volatile uint32_t* reg, uint32_t data)
{
    *(volatile uint32_t*) reg = data;
}
 
// Memory-Mapped I/O input
static inline uint32_t mmio_read(volatile uint32_t* reg)
{
    return *(volatile uint32_t*) reg;
}

void routing_core0cntv_to_core0irq(void)
{
    mmio_write(CORE0_TIMER_IRQCNTL, 0x08);
}

uint32_t read_core0timer_pending(void)
{
    uint32_t tmp;
    tmp = mmio_read(CORE0_IRQ_SOURCE);
    return tmp;
}

static uint32_t cntfrq = 0;

void enable_cntv(void)
{
    uint32_t cntv_ctl;
    cntv_ctl = 1;
	asm volatile ("msr cntv_ctl_el0, %0" :: "r" (cntv_ctl));
}

void disable_cntv(void)
{
    uint32_t cntv_ctl;
    cntv_ctl = 0;
	asm volatile ("msr cntv_ctl_el0, %0" :: "r" (cntv_ctl));
}

uint64_t read_cntvct(void)
{
	uint64_t val;
	asm volatile("mrs %0, cntvct_el0" : "=r" (val));
	return (val);
}

uint32_t read_cntv_tval(void)
{
    uint32_t val;
	asm volatile ("mrs %0, cntv_tval_el0" : "=r" (val));
    return val;
}

void write_cntv_tval(uint32_t val)
{
	asm volatile ("msr cntv_tval_el0, %0" :: "r" (val));
    return;
}

uint32_t read_cntfrq(void)
{
    uint32_t val;
	asm volatile ("mrs %0, cntfrq_el0" : "=r" (val));
    return val;
}

void init_timer(uint32_t usec)
{
    //uint32_t timer;
    cntfrq = read_cntfrq();
    //timer = cntfrq / 1e6;
    //timer *= usec;
    //write_cntv_tval(timer);
    cntfrq = cntfrq >> 2;
    write_cntv_tval(cntfrq);

    routing_core0cntv_to_core0irq();
    enable_cntv();

}

void set_timer(void)
{
    write_cntv_tval(cntfrq);
}

