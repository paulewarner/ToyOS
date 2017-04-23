#include "stdarg.h"
#include "tty.h"
#include "util.h"


void panic(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    printk("Kernel panic: ");
    vprintk(fmt, ap);
    asm("\t hlt");
}