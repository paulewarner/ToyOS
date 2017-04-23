#ifndef TTY_H
#define TTY_H

#include "stdarg.h"

void tty_init(void);
void printk(char *fmt, ...);
void clear_screen();
void vprintk(char *fmt, va_list ap);

#endif /* TTY_H */