#include "types.h"
#include "tty.h"
#include "io.h"

#define VMEM 0xB8000
#define COLOR 0x07 // grey on black

#define CRTOUT 0x3D4
#define CRTIN CRTOUT+1
#define CURSOR_POS_LOWER 0xF
#define CURSOR_POS_UPPER 0xE

#define COLS 80
#define ROWS 25

#define BUFSIZE 16

void PutChar(char c);
void PrintString(char *s);

int cursor = 0;

void PrintNumber(unsigned int n, int radix, int issigned)
{
    char buf[BUFSIZE];
    int i = 0, sign = 0, mod;
    if (issigned && (sign = n) < 0) {
        n = -n;
        buf[i++] = '-';
    }
    do {
        mod = (issigned ? -n : n) % radix;
        buf[i++] = mod < 10 ? mod + '0' : mod - 10 + 'a';
    } while (n /= radix);
    // if (sign < 0)
    //     buf[i++] = '-';
    if (issigned) {
        int x = 0;
        while (x < i)
            PutChar(buf[x++]);
    } else {
        while (i) {
            PutChar(buf[--i]);
        }
    }
    return;
}

void TTYInit()
{
    outb(0x3d4, 14);
    cursor = ((unsigned char)inb(0x3d4+1)) << 8;
    outb(0x3d4, 15);
    cursor |= (unsigned char)inb(0x3d4+1);
}

void MoveCursor(int pos)
{
    cursor = pos;
    outb(CRTOUT, CURSOR_POS_LOWER);
    outb(CRTIN, (uint8_t)(pos & 0xFF));
    outb(CRTOUT, CURSOR_POS_UPPER);
    outb(CRTIN, (uint8_t)((pos >> 8) & 0xFF));
}

void PutChar(char c)
{
    char *vmem;
    switch(c) {
        case '\b':
            MoveCursor(cursor-1);
            PutChar(' ');
            MoveCursor(cursor-1);
            break;
        case '\t': // I wouldn't call this particularly elegant...
            PutChar(' ');
            PutChar(' ');
            PutChar(' ');
            PutChar(' ');
            break;
        case '\n':
            MoveCursor(cursor - (cursor % COLS) + COLS);
            break;
        default:
            vmem = (char *)VMEM;
            vmem[2*cursor] = c;
            vmem[2*cursor+1] = COLOR;
            MoveCursor(cursor+1);
    }
}

void PrintString(char *s)
{
    char c;
    while ((c = *s++) != '\0')
        PutChar(c);
}

void Printk(char *fmt, ...)
{
    if (!fmt)
        return;
    int *p = ((int *)&fmt) + 1;
    char c = 0, type;
    while ((c = *fmt++) != '\0') {
        if (c == '%') {
operand:
            type = *fmt++;
            switch (type) {
                case 'u':
                PrintNumber(*p++, 10, 0);
                case 'x':
                PrintNumber(*p++, 16, 0);
                break;
                case 'd':
                PrintNumber(*p++, 10, 1);
                break;
                case 'o':
                PrintNumber(*p++, 8, 0);
                case 's':
                PrintString((char *)*p++);
                case '#':
                PrintString(*fmt == 'x' ? "0x" : "0");
                goto operand;
                break;
                default:
                return; // error
            }
        } else {
            PutChar(c);
        }
    }
}

void ClearScreen()
{
    int i;
    char *vmem = (char *)VMEM;
    for (i = 0; i < COLS*ROWS; i += 2) {
        vmem[i] = ' ';
    }
    MoveCursor(0);
}