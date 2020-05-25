#include "printf.h"
#include "typedef.h"
#include "uart.h"
#include "timer.h"
#include "sched.h"

void handler_uart_irq()
{
    unsigned char c;
    c = (unsigned char) *UART0_DR; // read for clear tx interrupt.
    printf("irq_handler : %c\n", c);
}

void handler_timer_irq()
{
    set_timer();
    printf("timer_irq : not local\n");
    //timer_tick();
}

void handler_localtimer_irq()
{
    local_timer_clr_reload_reg_t temp = { .IntClear = 1, .Reload = 1 };
	QA7->TimerClearReload  = temp;

    
}