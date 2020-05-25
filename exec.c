#include "uart.h"
#include "exec.h"
#include "handler.h"
#include "printf.h"

void aaa(void)
{
    disable_irq();
    printf("aaa\n");
    enable_irq();
    while(1);
}

uint32_t *get_elr(void)
{
    uint32_t val;
	asm volatile ("mrs %0, elr_el1" : "=r" (val));
    return val;
}

void handle_irq(void)
{
    char c;
    // check inteerupt source
    disable_irq();
    if (*CORE0_INTERRUPT_SOURCE & (1 << 8)) {
        if (*IRQ_BASIC & (1 << 9)) {
            if (*IRQ_PEND2 & (1 << 25)) {
                if (*UART0_MIS & (1 << 4)) {
                    handler_uart_irq();
                    return;
                }
            }
        }
    }

    if (read_core0timer_pending() & 0x08 ) {
        handler_timer_irq();
    }

    else{
        handler_localtimer_irq();
        set_elr(&aaa);
        //printf("timer elr : %10x\naaaaddress = :%10x\n", get_elr(), &aaa);
    }
    printf("end_exception\n");

    //enable_irq();
    return;
}
	uint64_t x0;
	uint64_t x1;
	uint64_t x2;
	uint64_t x3;
	uint64_t x4;
	uint64_t x5;
	uint64_t x6;
	uint64_t x7;
	uint64_t x8;


void exc_handler(unsigned long type, unsigned long esr, unsigned long elr, unsigned long spsr, unsigned long far)
{
    // print out interruption type
    switch(type) {
        case 0: uart_puts("Synchronous"); break;
        case 1: uart_puts("IRQ"); break;
        case 2: uart_puts("FIQ"); break;
        case 3: uart_puts("SError"); break;
    }
    uart_puts(": ");
    // decode exception type (some, not all. See ARM DDI0487B_b chapter D10.2.28)
    switch(esr>>26) {
        case 0b000000: uart_puts("Unknown"); break;
        case 0b000001: uart_puts("Trapped WFI/WFE"); break;
        case 0b001110: uart_puts("Illegal execution"); break;
        case 0b010101: uart_puts("System call"); break;
        case 0b100000: uart_puts("Instruction abort, lower EL"); break;
        case 0b100001: uart_puts("Instruction abort, same EL"); break;
        case 0b100010: uart_puts("Instruction alignment fault"); break;
        case 0b100100: uart_puts("Data abort, lower EL"); break;
        case 0b100101: uart_puts("Data abort, same EL"); break;
        case 0b100110: uart_puts("Stack alignment fault"); break;
        case 0b101100: uart_puts("Floating point"); break;
        default: uart_puts("Unknown"); break;
    }
    // decode data abort cause
    if(esr>>26==0b100100 || esr>>26==0b100101) {
        uart_puts(", ");
        switch((esr>>2)&0x3) {
            case 0: uart_puts("Address size fault"); break;
            case 1: uart_puts("Translation fault"); break;
            case 2: uart_puts("Access flag fault"); break;
            case 3: uart_puts("Permission fault"); break;
        }
        switch(esr&0x3) {
            case 0: uart_puts(" at level 0"); break;
            case 1: uart_puts(" at level 1"); break;
            case 2: uart_puts(" at level 2"); break;
            case 3: uart_puts(" at level 3"); break;
        }
    }
    // dump registers
    uart_puts(":\n  ESR_EL1 ");
    uart_hex(esr>>32);
    uart_hex(esr);
    uart_puts(" ELR_EL1 ");
    uart_hex(elr>>32);
    uart_hex(elr);
    uart_puts("\n SPSR_EL1 ");
    uart_hex(spsr>>32);
    uart_hex(spsr);
    uart_puts(" FAR_EL1 ");
    uart_hex(far>>32);
    uart_hex(far);
    uart_puts("\n");
    // no return from exception for now
    while(1);
}