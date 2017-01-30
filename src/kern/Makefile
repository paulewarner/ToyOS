AS = nasm
CC = gcc
LD = ld
CFLAGS += -fno-stack-protector -static -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -O -fno-pic -nostdinc -I$(INC)
ASFLAGS += -i $(INC)/

kernel: main.o tty.o io.o header.o entry.o kernel.ld
	$(LD) -e start -n -T kernel.ld -o kernel main.o tty.o io.o header.o entry.o

header.o: header.S
	$(AS) -f elf64 header.S -o header.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

tty.o: tty.c
	$(CC) $(CFLAGS) -c tty.c

io.o: io.S
	$(AS) $(ASFLAGS) -f elf64 io.S

entry.o: entry.S
	$(AS) $(ASFLAGS) -f elf64 entry.S

clean:
	rm -rf *.o
	rm -rf kernel

