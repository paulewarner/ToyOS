#include "tty.h"
#include "vm.h"

extern char end[]; /* has to be an array (for some reason), created in linker script */

void kalloc_init(void)
{
    printk("%#x\n", end);
}