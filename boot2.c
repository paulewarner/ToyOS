// Bootloader, stage 2
// This is more or less a normal ELF binary, but with a few small differences
// This file can't have any uninitalized variables in it!
#include "elf.h"

#define BUFSIZE 8

extern void PrintString(char *s);
extern void insl(void *dst, int offset);

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

void PrintNumber(int n)
{
    char buf[BUFSIZE];
    int i = 0;
    while (n) {
        buf[i++] = (n % 10) + '0';
        n /= 10;
    }
    buf[i] = '\0';
    reverse(buf);
    PrintString(buf);
}

void LoadKernel(int i)
{
    PrintNumber(i);
    PrintString(i == 0 ? "Yes" : "No");
//    PrintString(i);
    return;
}
