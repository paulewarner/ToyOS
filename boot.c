
typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;

extern void PrintString32(char *s);
extern char inb(uint16_t port);
extern void outb(uint16_t port, uint8_t value);

#define SECTOR_SIZE 512
#define BUFSIZE 16
/*
void reverse(char *s)
{
  char c, *end = s;
  while (*++end != '\0')
    ;
  end--;
  while (s != end) {
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
  //reverse(buffer);
  PrintString32(buffer);
  }*/

void ReadSector()
{
  
}


void LoadStage2()
{
}
