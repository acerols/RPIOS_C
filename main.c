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
#include "mbox.h"
#include "utils.h"
#include "timer.h"
#include "irq.h"
#include "typedef.h"

extern uint32_t cntfrq;

void main()
{
    // set up serial console
    uint32_t val;

    uart_puts("CNTFRQ  : ");
    cntfrq = read_cntfrq();
    uart_hex(cntfrq);

    write_cntv_tval(cntfrq);    // clear cntv interrupt and set next 1 sec timer.
    uart_puts("CNTV_TVAL: ");
    val = read_cntv_tval();
    uart_hex(val);
 
    routing_core0cntv_to_core0irq();
    enable_cntv(); 
    enable_irq();

    /*
    uart_puts("exception level = ");
    int el = get_el();
    uart_hex(el);
    uart_puts("\n");
    */
    while(1){
        uart_send(uart_getc());
    }
    

}