#include "typedef.h"

#define UART0_DR   ((volatile uint32_t *)(0x3F201000))
#define UART0_FR   ((volatile uint32_t *)(0x3F201018))
#define UART0_IMSC ((volatile uint32_t *)(0x3F201038))
#define UART0_MIS  ((volatile uint32_t *)(0x3F201040))
#define IRQ_BASIC   ((volatile uint32_t *)(0x3F00B200))
#define IRQ_PEND2   ((volatile uint32_t *)(0x3F00B208))
#define IRQ_ENABLE2 ((volatile uint32_t *)(0x3F00B214))
#define GPU_INTERRUPTS_ROUTING ((volatile uint32_t *)(0x4000000C))
#define CORE0_INTERRUPT_SOURCE ((volatile uint32_t *)(0x40000060))

typedef unsigned int* intptr_t;

// Memory-Mapped I/O output
static inline void mmio_write(intptr_t reg, uint32_t data)
{
    *(volatile uint32_t*) reg = data;
}
 
// Memory-Mapped I/O input
static inline uint32_t mmio_read(intptr_t reg)
{
    return *(volatile uint32_t*) reg;
}

#define CORE0_TIMER_IRQCNTL 0x40000040
#define CORE0_IRQ_SOURCE    0x40000060

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

uint32_t cntfrq = 0;

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

void set_spsel(void)
{
    uint32_t val = 1;
    asm volatile("msr SPSel, %0" :: "r" (val));
    return;
}