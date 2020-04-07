#include "uart.h"
#include "exec.h"
#include "timer.h"

void handle_irq(void)
{
    char c;
    // check inteerupt source
    disable_irq();
    if (*CORE0_INTERRUPT_SOURCE & (1 << 8)) {
        if (*IRQ_BASIC & (1 << 9)) {
            if (*IRQ_PEND2 & (1 << 25)) {
                if (*UART0_MIS & (1 << 4)) {
                    c = (unsigned char) *UART0_DR; // read for clear tx interrupt.
                    uart_send(c);
                    uart_puts(" c_irq_handler\n");
                    return;
                }
            }
        }
    }

    if (read_core0timer_pending() & 0x08 ) {
        set_timer();
        uart_puts(" timer_handler\n");
    }

    enable_irq();
    return;
}