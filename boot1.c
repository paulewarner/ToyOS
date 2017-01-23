
typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

extern void PrintString(char *s);
extern char inb(uint16_t port);
extern void outb(uint16_t port, uint8_t value);
extern void insl(uint16_t port, void *dst, int count);

#define SECTOR_SIZE 512
#define BUFSIZE 8

/*
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
  int i = 0;
  char buffer[BUFSIZE];
  while (n) {
    buffer[i++] = (n % 10) + '0';
    n /= 10;
  }
  buffer[i] = '\0';
  reverse(buffer);
  PrintString32(buffer);
}*/

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

// Load the second stage of the bootloader
void LoadStage2()
{ 
  // unsigned char c = 0, b = 0;
  // unsigned char *dst = (unsigned char *)0x10000; // scratch space
  // ReadSector(dst, SECTOR_SIZE-1);
  // c = dst[SECTOR_SIZE-1];
  // b = dst[SECTOR_SIZE-2];
  PrintString("Yes");
  // PrintString(b == 0x55 ? "Yes" : "No");
}
