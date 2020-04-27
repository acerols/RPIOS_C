#include "typedef.h"

void register_dump(uint64_t reg[])
{
    uint64_t temp;
    asm volatile("mov %0, x0" : "=r" (temp));
    reg[0] = temp;
    asm volatile("mov %0, x1" : "=r" (temp));
    reg[1] = temp;
    asm volatile("mov %0, x2" : "=r" (temp));
    reg[2] = temp;
    asm volatile("mov %0, x3" : "=r" (temp));
    reg[3] = temp;
    asm volatile("mov %0, x4" : "=r" (temp));
    reg[4] = temp;
    asm volatile("mov %0, x5" : "=r" (temp));
    reg[5] = temp;
    asm volatile("mov %0, x6" : "=r" (temp));
    reg[6] = temp;
    asm volatile("mov %0, x7" : "=r" (temp));
    reg[7] = temp;
    asm volatile("mov %0, x9" : "=r" (temp));
    reg[8] = temp;
    asm volatile("mov %0, x10" : "=r" (temp));
    reg[10] = temp;
    asm volatile("mov %0, x11" : "=r" (temp));
    reg[11] = temp;
    asm volatile("mov %0, x12" : "=r" (temp));
    reg[12] = temp;
    asm volatile("mov %0, x13" : "=r" (temp));
    reg[13] = temp;
    asm volatile("mov %0, x14" : "=r" (temp));
    reg[14] = temp;
    asm volatile("mov %0, x15" : "=r" (temp));
    reg[15] = temp;
    asm volatile("mov %0, x16" : "=r" (temp));
    reg[16] = temp;
    asm volatile("mov %0, x17" : "=r" (temp));
    reg[17] = temp;
    asm volatile("mov %0, x18" : "=r" (temp));
    reg[18] = temp;
    asm volatile("mov %0, x19" : "=r" (temp));
    reg[19] = temp;
    asm volatile("mov %0, x20" : "=r" (temp));
    reg[20] = temp;
    asm volatile("mov %0, x21" : "=r" (temp));
    reg[21] = temp;
    asm volatile("mov %0, x22" : "=r" (temp));
    reg[22] = temp;
    asm volatile("mov %0, x23" : "=r" (temp));
    reg[23] = temp;
    asm volatile("mov %0, x24" : "=r" (temp));
    reg[24] = temp;
    asm volatile("mov %0, x25" : "=r" (temp));
    reg[25] = temp;
    asm volatile("mov %0, x26" : "=r" (temp));
    reg[26] = temp;
    asm volatile("mov %0, x27" : "=r" (temp));
    reg[27] = temp;
    asm volatile("mov %0, x28" : "=r" (temp));
    reg[28] = temp;
    asm volatile("mov %0, x29" : "=r" (temp));
    reg[29] = temp;
    asm volatile("mov %0, x30" : "=r" (temp));
    reg[30] = temp;
    asm volatile("mov %0, x31" : "=r" (temp));
    reg[31] = temp;
    
    return;
}


