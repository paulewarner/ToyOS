
AS = nasm
CC = gcc
CFLAGS = -fno-stack-protector -static -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -O -fno-pic -nostdinc -I.
LD = ld

drive: bootblock
	./writedisk.py bootblock bootblock.o boot.elf

bootblock: boot1.o io.o boot.o
	$(LD) -melf_i386 -N -e start -Ttext 0x7C00 -o bootblock.o boot.o boot1.o io.o

boot1.o: boot1.c
	$(CC) $(CFLAGS) -m32 -c boot1.c

io.o: io.S
	$(AS)  -f elf -o io.o io.S

boot.o: boot.S
	$(AS) -f elf -o boot.o boot.S

qemu: drive
	qemu-system-x86_64 -drive file=bootblock,index=0,media=disk,format=raw,index=0


# boot2.elf:
# 	$(CC) $(CLFAGS) -m32 boot2.c