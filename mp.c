#include "typedef.h"
#include "printf.h"

uint32_t get_pn()
{
    uint32_t ProcessNumber;
    asm volatile("mrs   %0, mpidr_el1" : "=r"(ProcessNumber));
    ProcessNumber = ProcessNumber & 0xff;
    return ProcessNumber;
}

uint32_t mplock[4];

void mpJob()
{
    printf("%d\n", get_pn());
    while(1){
        if(mplock[get_pn()] == 1){
            printf("%d\n", get_pn());
            mplock[get_pn()] = 0;
        }
    }
}