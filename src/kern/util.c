#include "stdarg.h"
#include "tty.h"
#include "util.h"


void panic(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    Printk("Kernel panic: ");
    VPrintk(fmt, ap);
}