#include "tty.h"
#include "vm.h"

extern char end[]; /* has to be an array (for some reason), created in linker script */

void KAllocInit(void)
{
    Printk("%#x\n", end);
}