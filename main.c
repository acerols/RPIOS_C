#include "uart.h"
#include "rand.h"
#include "timer.h"
#include "typedef.h"
#include "printf.h"
#include "sched.h"
#include "localtimer.h"

void process(char *array)
{
    while(1){
        for(int i = 0; i < 5; i++){
            printf("%c", array[i]);
            delay(100000);
        }
    }
}

uint64_t reg[32];

void main()
{
    // set up serial console and random number generator
    uart_init();
    rand_init();
    printf("printf\n");
    init_timer(1);
    init_localtimer();
    enable_irq();

    

    int response = copy_process((unsigned long)&process, (unsigned long)"123456");
    printf("%d %10x\n", response, &process);
    response = copy_process((unsigned long)&process, (unsigned long)"67890");
    printf("%d %10x\n", response, &process);

    // echo everything back
    while(1) {
        //schedule();
    }
}

