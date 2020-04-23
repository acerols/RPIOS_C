#include "printf.h"
#include "typedef.h"
#include "uart.h"
#include "timer.h"

void handler_uart_irq()
{
    unsigned char c;
    c = (unsigned char) *UART0_DR; // read for clear tx interrupt.
    printf("irq_handler : %c\n", c);
}

void handler_timer_irq()
{
    set_timer();
    uart_puts("timer_handler\n");
}