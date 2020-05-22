#include "uart.h"
#include "rand.h"
#include "timer.h"
#include "typedef.h"
#include "printf.h"
#include "sched.h"

void process(char *array)
{
    while(1){
        for(int i = 0; i < 5; i++){
            printf("%c", array[i]);
            delay(100000);
        }
    }
}

void main()
{
    // set up serial console and random number generator
    uart_init();
    rand_init();
    printf("printf\n");
    init_timer(1);
    enable_irq();

    uint64_t reg[32];

    int response = copy_process((unsigned long)&process, (unsigned long)"123456");
    printf("%d %10x\n", response, &process);
    response = copy_process((unsigned long)&process, (unsigned long)"67890");
    printf("%d %10x\n", response, &process);


    register_dump(reg);

    for(int i = 0; i+1 < 32; i+=2)
        printf("x%d : %8x | x%d : %8x \n", i, reg[i], i+1, reg[i+1]);

    // echo everything back
    while(1) {
        //schedule();
    }
}

