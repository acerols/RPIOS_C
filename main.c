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
    QA7->TimerRouting.Routing = LOCALTIMER_TO_CORE0_IRQ;			// Route local timer IRQ to Core0

	QA7->TimerControlStatus.ReloadValue = 100;						// Timer period set
	//QA7->TimerControlStatus.TimerEnable = 1;						// Timer enabled
    //QA7->TimerControlStatus.IntEnable = 1;							// Timer IRQ enabled

	QA7->TimerClearReload.IntClear = 1;								// Clear interrupt
	QA7->TimerClearReload.Reload = 1;								// Reload now

	QA7->Core0TimerIntControl.nCNTPNSIRQ_IRQ = 1;					// We are in NS EL1 so enable IRQ to core0 that level
	QA7->Core0TimerIntControl.nCNTPNSIRQ_FIQ = 0;					// Make sure FIQ is zero
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




/* Here is your interrupt function */
void __attribute__((interrupt("IRQ")))  irq_handler_stub(void) {

       /* You code goes here */

	local_timer_clr_reload_reg_t temp = { .IntClear = 1, .Reload = 1 };
	QA7->TimerClearReload  = temp;									// Clear interrupt & reload
}

/* here is your main 
int main(void) {

	QA7->TimerRouting.Routing = LOCALTIMER_TO_CORE0_IRQ;			// Route local timer IRQ to Core0

	QA7->TimerControlStatus.ReloadValue = 100;						// Timer period set
	QA7->TimerControlStatus.TimerEnable = 1;						// Timer enabled
	QA7->TimerControlStatus.IntEnable = 1;							// Timer IRQ enabled

	QA7->TimerClearReload.IntClear = 1;								// Clear interrupt
	QA7->TimerClearReload.Reload = 1;								// Reload now

	QA7->Core0TimerIntControl.nCNTPNSIRQ_IRQ = 1;					// We are in NS EL1 so enable IRQ to core0 that level
	QA7->Core0TimerIntControl.nCNTPNSIRQ_FIQ = 0;					// Make sure FIQ is zero

	EnableInterrupts();												// Start interrupts rolling

	while (1) {
	}

	return(0);
}
*/
