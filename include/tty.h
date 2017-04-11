#ifndef TTY_H
#define TTY_H

#include "stdarg.h"

void TTYInit(void);
void Printk(char *fmt, ...);
void ClearScreen();
void VPrintk(char *fmt, va_list ap);

#endif /* TTY_H */