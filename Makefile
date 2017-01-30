
AS = nasm
CC = gcc
CFLAGS = -fno-stack-protector -static -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -O -fno-pic -nostdinc -I.
LD = ld

drive: bootblock boot.elf writedisk.py
	./writedisk.py bootblock bootblock.o boot.elf

bootblock: boot1.o io.o boot.o disk.o
	$(LD) -melf_i386 -N -e start -Ttext 0x7C00 -o bootblock.o boot.o boot1.o io.o disk.o

boot1.o: boot1.c elf.h
	$(CC) $(CFLAGS) -m32 -c boot1.c

io.o: io.S
	$(AS) -f elf64 -o io.o io.S

boot.o: boot.S
	$(AS) -f elf64 -o boot.o boot.S

qemu: drive
	qemu-system-x86_64 -drive file=bootblock,index=0,media=disk,format=raw,index=0

boot.elf: io.o boot2.c tty.o disk.o
	$(CC) $(CFLAGS) -m32 -c boot2.c
	$(LD) -melf_i386 -N -e LoadKernel -Ttext 0x10000 -o boot.elf boot2.o io.o disk.o tty.o

kernel: main.o tty.o io.o header.o
	$(LD) -n -e Main -T kernel.ld -o kernel main.o tty.o io.o header.o

header.o: header.S
	$(AS) -f elf64 header.S -o header.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

disk.o: disk.c disk.h
	$(CC) $(CFLAGS) -m32 -c disk.c

tty.o: tty.c tty.h
	$(CC) $(CFLAGS) -c tty.c

clean:
	rm -rf *.o kernel boot.elf bootblock
