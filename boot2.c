// Bootloader, stage 2
// This is more or less a normal ELF binary, but with a few small differences
// This file can't have any uninitalized variables in it!

extern void PrintString(char *s);

int LoadKernel()
{
   PrintString("Stage 2 Loaded!"); 
}