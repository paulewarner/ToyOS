#include "elf.h"

typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

extern void PrintString(char *s);
extern char inb(uint16_t port);
extern void outb(uint16_t port, uint8_t value);
extern void insl(uint16_t port, void *dst, int count);

#define SECTOR_SIZE 512

void waitdisk()
{
  while ((inb(0x1F7) & 0xC0) != 0x40)
    ;
}

void ReadSector(void *dst, uint32_t offset)
{
  waitdisk();
  outb(0x1F2, 1); // Number of sectors to read (one)
  outb(0x1F3, offset);
  outb(0x1F4, offset >> 8);
  outb(0x1F5, offset >> 16);
  outb(0x1F6, (offset >> 24) | 0xE0);
  outb(0x1F7, 0x20); // cmd 0x20: read sectors
  waitdisk();
  insl(0x1F0, dst, SECTOR_SIZE/4);
}

inline int streq(char *s1, char *s2, int size)
{
  while (--size)
    if (*s1++ != *s2++)
      return 0;
    return 1;
}

// Load the second stage of the bootloader
void LoadStage2()
{
  struct ElfHeader *hdr;
  void (*start)(int);
  unsigned char *dst = (unsigned char *)0x10000 - 0x84; // 0x84 is the offset of .text section in bootloader
  ReadSector(dst, 1);
  int size = *(int *)dst;
  hdr = (struct ElfHeader *)(dst + sizeof(size));
  if (!streq((char *)hdr->e_ident, ELF_MAG, 4))
    return;  // Bad executable
  size -= SECTOR_SIZE-4;
  int i = 2;
  while (size > 0) {
    dst += SECTOR_SIZE;
    ReadSector(dst, i++);
    size -= SECTOR_SIZE;
  }
  start = (void(*)(int))hdr->e_entry;
  // PrintString((int)start == 0x10000 ? "Yes" : "No");
  start(0); // Never to return
}
