/*
 * Copyright (C) 2018 bzt (bztsrc@github)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#include "uart.h"
#include "rand.h"
#include "timer.h"
#include "typedef.h"

#define IRQ_BASIC   ((volatile uint32_t *)(0x3F00B200))
#define IRQ_PEND2   ((volatile uint32_t *)(0x3F00B208))
#define IRQ_ENABLE2 ((volatile uint32_t *)(0x3F00B214))
#define GPU_INTERRUPTS_ROUTING ((volatile uint32_t *)(0x4000000C))
#define CORE0_INTERRUPT_SOURCE ((volatile uint32_t *)(0x40000060))

void main()
{
    // set up serial console and random number generator
    uart_init();
    rand_init();
    
    // enable UART RX interrupt.
    
    *UART0_IMSC = 1 << 4;

    // UART interrupt routing.
    *IRQ_ENABLE2 = 1 << 25;

    // IRQ routeing to CORE0.
    *GPU_INTERRUPTS_ROUTING = 0x00;

    /*
    uart_puts("Here goes a random number: ");
    uart_hex(rand(0,4294967295));
    uart_puts("\n");
    */

    init_timer(1);

    enable_irq();

    // echo everything back
    while(1) {
        uart_send(uart_getc());
    }
}

