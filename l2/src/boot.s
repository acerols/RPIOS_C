#include "arm/sysregs.h"

#include "mm.h"

.section ".text.boot"

.global _start
_start:
    mrs     x0, mpidr_el1
    and     x0, x0, #0xff
    cbz     x0, master
    boot    proc_hang

proc_hang:
    b   proc_hang

master:
    ldr     x0, =SCTLR_VALUE_MMU_DISABLED
    mrs     sctlr_el1, x0
    
    ldr     x0, =HCR_VALUE
    mrs     hcr_el2, x0