#ifndef __LOCALTIMER_H__
#define __LOCALTIMER_H__

#include "typedef.h"

/*--------------------------------------------------------------------------}
{    LOCAL TIMER INTERRUPT ROUTING REGISTER - QA7_rev3.4.pdf page 18		}
{--------------------------------------------------------------------------*/
typedef union
{
	struct
	{
		enum {
			LOCALTIMER_TO_CORE0_IRQ = 0,
			LOCALTIMER_TO_CORE1_IRQ = 1,
			LOCALTIMER_TO_CORE2_IRQ = 2,
			LOCALTIMER_TO_CORE3_IRQ = 3,
			LOCALTIMER_TO_CORE0_FIQ = 4,
			LOCALTIMER_TO_CORE1_FIQ = 5,
			LOCALTIMER_TO_CORE2_FIQ = 6,
			LOCALTIMER_TO_CORE3_FIQ = 7,
		} Routing: 3;												// @0-2	  Local Timer routing 
		unsigned unused : 29;										// @3-31
	};
	uint32_t Raw32;													// Union to access all 32 bits as a uint32_t
} local_timer_int_route_reg_t;

/*--------------------------------------------------------------------------}
{    LOCAL TIMER CONTROL AND STATUS REGISTER - QA7_rev3.4.pdf page 17		}
{--------------------------------------------------------------------------*/
typedef union
{
	struct
	{
		unsigned ReloadValue : 28;									// @0-27  Reload value 
		unsigned TimerEnable : 1;									// @28	  Timer enable (1 = enabled) 
		unsigned IntEnable : 1;										// @29	  Interrupt enable (1= enabled)
		unsigned unused : 1;										// @30	  Unused
		unsigned IntPending : 1;									// @31	  Timer Interrupt flag (Read-Only) 
	};
	uint32_t Raw32;													// Union to access all 32 bits as a uint32_t
} local_timer_ctrl_status_reg_t;

/*--------------------------------------------------------------------------}
{     LOCAL TIMER CLEAR AND RELOAD REGISTER - QA7_rev3.4.pdf page 18		}
{--------------------------------------------------------------------------*/
typedef union
{
	struct
	{
		unsigned unused : 30;										// @0-29  unused 
		unsigned Reload : 1;										// @30	  Local timer-reloaded when written as 1 
		unsigned IntClear : 1;										// @31	  Interrupt flag clear when written as 1  
	};
	uint32_t Raw32;													// Union to access all 32 bits as a uint32_t
} local_timer_clr_reload_reg_t;

/*--------------------------------------------------------------------------}
{    GENERIC TIMER INTERRUPT CONTROL REGISTER - QA7_rev3.4.pdf page 13		}
{--------------------------------------------------------------------------*/
typedef union
{
	struct
	{
		unsigned nCNTPSIRQ_IRQ : 1;									// @0	Secure physical timer event IRQ enabled, This bit is only valid if bit 4 is clear otherwise it is ignored. 
		unsigned nCNTPNSIRQ_IRQ : 1;								// @1	Non-secure physical timer event IRQ enabled, This bit is only valid if bit 5 is clear otherwise it is ignored
		unsigned nCNTHPIRQ_IRQ : 1;									// @2	Hypervisor physical timer event IRQ enabled, This bit is only valid if bit 6 is clear otherwise it is ignored
		unsigned nCNTVIRQ_IRQ : 1;									// @3	Virtual physical timer event IRQ enabled, This bit is only valid if bit 7 is clear otherwise it is ignored
		unsigned nCNTPSIRQ_FIQ : 1;									// @4	Secure physical timer event FIQ enabled, If set, this bit overrides the IRQ bit (0) 
		unsigned nCNTPNSIRQ_FIQ : 1;								// @5	Non-secure physical timer event FIQ enabled, If set, this bit overrides the IRQ bit (1)
		unsigned nCNTHPIRQ_FIQ : 1;									// @6	Hypervisor physical timer event FIQ enabled, If set, this bit overrides the IRQ bit (2)
		unsigned nCNTVIRQ_FIQ : 1;									// @7	Virtual physical timer event FIQ enabled, If set, this bit overrides the IRQ bit (3)
		unsigned reserved : 24;										// @8-31 reserved
	};
	uint32_t Raw32;													// Union to access all 32 bits as a uint32_t
} generic_timer_int_ctrl_reg_t;

struct __attribute__((__packed__, aligned(4))) QA7Registers {
	local_timer_int_route_reg_t TimerRouting;						// 0x24
	uint32_t GPIORouting;											// 0x28
	uint32_t AXIOutstandingCounters;								// 0x2C
	uint32_t AXIOutstandingIrq;										// 0x30
	local_timer_ctrl_status_reg_t TimerControlStatus;				// 0x34
	local_timer_clr_reload_reg_t TimerClearReload;					// 0x38
	uint32_t unused;												// 0x3C
	generic_timer_int_ctrl_reg_t Core0TimerIntControl;				// 0x40
	generic_timer_int_ctrl_reg_t Core1TimerIntControl;				// 0x44
	generic_timer_int_ctrl_reg_t Core2TimerIntControl;				// 0x48
	generic_timer_int_ctrl_reg_t Core3TimerIntControl;				// 0x4C
};

#define QA7 ((volatile __attribute__((aligned(4))) struct QA7Registers*)(uint32_t *)(0x40000024))

void init_localtimer();
void set_localtimer();

#endif