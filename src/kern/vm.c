#include "tty.h"
#include "vm.h"

extern char end[]; /* has to be an array (for some reason), created in linker script */

void lcr3(uint64_t val)
{
    asm volatile("mov %%rdi, %%cr3" : "=r" (val));
}

uint64_t rcr3()
{
    uint64_t val;
    asm volatile("mov %%cr3, %%rax" : "=r" (val));
    return val;
}

void kalloc_init(void)
{
    printk("%#x\n", end);
}