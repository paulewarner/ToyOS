#include "elf.h"
#include "disk.h"

inline int streq(char *s1, char *s2, int size)
{
  while (--size)
    if (*s1++ != *s2++)
      return 0;
    return 1;
}

extern void PrintString(char *s);

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
  start(i); // Never to return
}
