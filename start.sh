nasm boot.S -f elf -o boot.o
nasm io.S -f elf -o io.o
gcc -m32 -fno-stack-protector -static -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -O -fno-pic -nostdinc -I. -c boot.c -o bootc.o
ld -melf_i386 -N -e start -Ttext 0x7C00 -o bootblock.o boot.o bootc.o io.o
objcopy -S -O binary -j .text bootblock.o bootblock
./sign.py bootblock
qemu-system-x86_64 -drive file=bootblock,index=0,media=disk,format=raw,index=0
