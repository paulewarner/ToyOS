#include "types.h"
#include "tty.h"

#define VMEM 0xB8000
#define COLOR 0x07 // grey on black

#define CRTOUT 0x3D4
#define CRTIN CRTOUT+1
#define CURSOR_POS_LOWER 0xF
#define CURSOR_POS_UPPER 0xE

#define COLS 80
#define ROWS 25

#define BUFSIZE 16

extern uint8_t inb(uint16_t);
extern void outb(uint16_t, uint16_t);

void PutChar(char c);
void PrintString(char *s);

int cursor = 0;

void reverse(char *s)
{
  char c, *end = s;
  while (*++end != '\0')
    ;
  end--;
  while (s < end) {
    c = *s;
    *s++ = *end;
    *end-- = c;
  }
}

void PrintNumber(int n, int radix)
{
    char buf[BUFSIZE];
    int i = 0, sign, mod;
    if ((sign = n) < 0)
        n = -n;
    do {
        mod = n % radix;
        buf[i++] = mod < 10 ? mod + '0' : mod + 'A';
    } while (n /= radix);
    if (sign < 0)
        buf[i++] = '-';
    buf[i] = '\0';
    reverse(buf);
    PrintString(buf);
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

void Printf(char *fmt, ...)
{
    if (!fmt)
        return;
    int *p = ((int *)&fmt) + 1;
    char c = 0;
    while ((c = *fmt++) != '\0') {
        if (c == '%') {
            char type = *fmt++;
            switch (type) {
                case 'x':
                PrintNumber(*p++, 16);
                break;
                case 'd':
                PrintNumber(*p++, 10);
                break;
                case 's':
                PrintString((char *)*p++);
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
    // PutChar(cursor + '0');
}