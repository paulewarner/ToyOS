CC = clang
LD = ld

SRC = $(CURDIR)/src
BUILD = $(CURDIR)/build
INC = -I$(CURDIR)/include

export

SRCFILES := $(shell find $(1) -type f -name '*.c' -or -name "*.py" -or -name "*.ld" -or -name "*.S" -or -name "*.h")

os.iso: $(call SRCFILES, src/kern) $(call SRCFILES include)
	$(MAKE) -C src/kern kernel $(INC)
	rm -rf isofiles
	mkdir isofiles
	mkdir isofiles/boot
	mkdir isofiles/boot/grub
	cp grub.cfg isofiles/boot/grub
	cp src/kern/kernel isofiles/boot
	grub-mkrescue -d deps/grub/i386-pc -o os.iso isofiles
	rm -rf isofiles

drive: writedisk.py $(call SRCFILES src/boot) $(call SRCFILES include)
	# $(MAKE) -C src/boot $(INC)
	$(MAKE) -C src/kern kernel $(INC)
	cd $(BUILD)
	$(CURDIR)/writedisk.py $(CURDIR)/bootblock $(SRC)/boot/bootblock.o $(SRC)/boot/boot.elf

qemu: drive
	qemu-system-x86_64 -drive file=$(SRC)/boot/bootloader,index=0,media=disk,format=raw,index=0

qemu-grub: os.iso
	qemu-system-x86_64 -cdrom os.iso

qemu-grub-lldb: os.iso
	lldb -s $(CURDIR)/scripts/lldb-debug.py

qemu-grub-gdb: os.iso
	gdb -x $(CURDIR)/scripts/gdb-debug.py

clean:
	$(MAKE) -C src/kern clean
	$(MAKE) -C src/boot clean
	rm -rf os.iso
