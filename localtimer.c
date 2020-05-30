#include "timer.h"
#include "typedef.h"

void init_localtimer()
{
    QA7->TimerRouting.Routing = LOCALTIMER_TO_CORE0_IRQ;			// Route local timer IRQ to Core0

	QA7->TimerControlStatus.ReloadValue = 0x8FFF00;						// Timer period set
	QA7->TimerControlStatus.TimerEnable = 1;						// Timer enabled
    QA7->TimerControlStatus.IntEnable = 1;							// Timer IRQ enabled

	QA7->TimerClearReload.IntClear = 1;								// Clear interrupt
	QA7->TimerClearReload.Reload = 1;								// Reload now

	QA7->Core0TimerIntControl.nCNTPNSIRQ_IRQ = 1;					// We are in NS EL1 so enable IRQ to core0 that level
	QA7->Core0TimerIntControl.nCNTPNSIRQ_FIQ = 0;					// Make sure FIQ is zero
}

void set_localtimer()
{
    local_timer_clr_reload_reg_t temp = { .IntClear = 1, .Reload = 1 };
	QA7->TimerClearReload  = temp;
}

