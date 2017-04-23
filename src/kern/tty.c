#include "types.h"
#include "tty.h"
#include "io.h"
#include "stdarg.h"

#define VMEM 0xB8000
#define COLOR 0x07 // grey on black

#define CRTOUT 0x3D4
#define CRTIN CRTOUT+1
#define CURSOR_POS_LOWER 0xF
#define CURSOR_POS_UPPER 0xE

#define COLS 80
#define ROWS 25

#define BUFSIZE 16

void putchar(char c);
void print_string(char *s);

int cursor = 0;

void print_number(unsigned int n, int radix, int issigned)
{

    char buf[BUFSIZE];
    int i = 0, sign = 0, mod;
    if (issigned && (sign = n) < 0) {
        n = -n;
    }
    do {
        mod = (issigned ? -n : n) % radix;
        buf[i++] = mod < 10 ? mod + '0' : mod - 10 + 'a';
    } while (n /= radix);
    if (sign < 0)
        buf[i++] = '-';
    if (issigned) {
        int x = 0;
        while (x < i)
            putchar(buf[x++]);
    } else {
        while (i) {
            putchar(buf[--i]);
        }
    }
    return;
}

void tty_init()
{
    outb(0x3d4, 14);
    cursor = ((unsigned char)inb(0x3d4+1)) << 8;
    outb(0x3d4, 15);
    cursor |= (unsigned char)inb(0x3d4+1);
}

void move_cursor(int pos)
{
    cursor = pos;
    outb(CRTOUT, CURSOR_POS_LOWER);
    outb(CRTIN, (uint8_t)(pos & 0xFF));
    outb(CRTOUT, CURSOR_POS_UPPER);
    outb(CRTIN, (uint8_t)((pos >> 8) & 0xFF));
}

void putchar(char c)
{
    char *vmem;
    switch(c) {
        case '\b':
            move_cursor(cursor-1);
            putchar(' ');
            move_cursor(cursor-1);
            break;
        case '\t': // I wouldn't call this particularly elegant...
            putchar(' ');
            putchar(' ');
            putchar(' ');
            putchar(' ');
            break;
        case '\n':
            move_cursor(cursor - (cursor % COLS) + COLS);
            break;
        default:
            vmem = (char *)VMEM;
            vmem[2*cursor] = c;
            vmem[2*cursor+1] = COLOR;
            move_cursor(cursor+1);
    }
}

void print_string(char *s)
{
    char c;
    while ((c = *s++) != '\0')
        putchar(c);
}

void vprintk(char *fmt, va_list ap)
{
    char c = 0, type;
    while ((c = *fmt++) != '\0') {
        if (c == '%') {
operand:
            type = *fmt++;
            switch (type) {
                case 'u':
                print_number(va_arg(ap, unsigned int), 10, 0);
                case 'x':
                print_number(va_arg(ap, unsigned int), 16, 0);
                break;
                case 'd':
                print_number(va_arg(ap, unsigned int), 10, 1);
                break;
                case 'o':
                print_number(va_arg(ap, unsigned int), 8, 0);
                case 's':
                print_string(va_arg(ap, char *));
                case '#':
                print_string(*fmt == 'x' ? "0x" : "0");
                goto operand;
                break;
                default:
                return; // error
            }
        } else {
            putchar(c);
        }
    }
}

void printk(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintk(fmt, ap);
}

void clear_screen()
{
    int i;
    char *vmem = (char *)VMEM;
    for (i = 0; i < COLS*ROWS; i += 2) {
        vmem[i] = ' ';
    }
    move_cursor(0);
}