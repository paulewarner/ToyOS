#include "disk.h"
#include "io.h"

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