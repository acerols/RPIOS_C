#include "sys.h"

.globl call_sys_write
call_sys_write:
    mov x8, #SYS_WRITE_NUMBER
    svc #0
    ret