#include "uart.h"
#include "timer.h"

#define ENABLE_IRQS_1		(PBASE+0x0000B210)

void enable_interrupt_controller()
{
	put32(ENABLE_IRQS_1, SYSTEM_TIMER_IRQ_1);
}

void handle_irq()
{
    unsigned int irq = get32(IRQ_PENDING_1);
    uart_puts("call handler");
    switch(irq){
        case(SYSTEM_TIMER_IRQ_1):
            handle_timer_irq();
            break;
        default:
            uart_puts("Undefine pending irq: ");
            uart_hex(irq);
    }
    return;
}