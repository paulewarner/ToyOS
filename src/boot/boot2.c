// Bootloader, stage 2
// This is more or less a normal ELF binary, but with a few small differences
// This file can't have any uninitalized variables in it!
#include "elf.h"
#include "types.h"
#include "tty.h"

#define SECTOR_SIZE 512

void LoadKernel(int sector)
{
    TTYInit();
    Printk("%d", sector);
}
