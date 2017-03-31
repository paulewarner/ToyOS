# BUILD = ../build
# INC = ../include

# AS = nasm
# CC = gcc
# LD = ld
# CFLAGS += -fno-stack-protector -static -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -O -fno-pic -nostdinc -I$(INC)
# ASFLAGS += -i $(INC)/

# all: bootblock boot.elf

# bootblock: bootblock.o sign.py
# 	$(CURDIR)/sign.py bootblock bootblock.o
# 	cp bootblock $(BUILD)

# bootblock.o: boot1.o io32.o boot.o disk.o
# 	$(LD) -melf_i386 -N -e start -Ttext 0x7C00 -o bootblock.o boot.o boot1.o io32.o disk.o

# boot1.o: boot1.c
# 	$(CC) $(CFLAGS) -m32 -c boot1.c

# boot.o: boot.S
# 	$(AS) $(ASFLAGS) -f elf boot.S

# io32.o: io32.S
# 	$(AS) $(ASFLAGS) -f elf io32.S

# tty32.o: tty.c
# 	$(CC) $(CFLAGS) -m32 -c tty.c -o tty32.o

# disk.o: disk.c
# 	$(CC) $(CFLAGS) -m32 -c disk.c

# boot.elf: io32.o boot2.o tty32.o disk.o
# 	$(LD) -melf_i386 -N -e LoadKernel -Ttext 0x10000 -o boot.elf boot2.o io32.o disk.o tty32.o
# 	cp boot.elf $(BUILD)

# boot2.o: boot2.c
# 	$(CC) $(CFLAGS) -m32 -c boot2.c

# clean:
# 	rm -rf *.o boot.elf bootblock

AS = nasm

CFLAGS += -fno-stack-protector -static -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -O -fno-pic -nostdinc -m32 $(INC)
ASFLAGS += $(INC)/ -f elf32

$(echo INC)

DEPDIR = .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
COMPILE.S = $(AS) $(ASFLAGS) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

BOOTOBJS = io32.o  \
		   tty32.o \
		   disk.o  \
		   boot2.o \

BOOTBLOCKOBJS =  boot.o  \
				 io32.o  \
				 disk.o  \
				 boot1.o \
# 				 io32.o  \
# 				 boot.o  \
# 				 disk.o  \

all: bootloader

bootloader: boot.elf bootblock.o sign.py
	$(CURDIR)/sign.py bootloader bootblock.o boot.elf

boot.elf: $(BOOTOBJS)
	$(LD) -melf_i386 -N -e LoadKernel -Ttext 0x10000 -o boot.elf $(BOOTOBJS)

bootblock.o: $(BOOTBLOCKOBJS)
	$(LD) -melf_i386 -N -e start -Ttext 0x7C00 -o bootblock.o $(BOOTBLOCKOBJS)

%.o : %.S
%.o : %.S $(DEPDIR)/%.d
		$(COMPILE.S)  $(OUTPUT_OPTION) $<
		$(POSTCOMPILE)

%.o : %.c
%.o : %.c $(DEPDIR)/%.d
		$(COMPILE.c) $(OUTPUT_OPTION) $<
		$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))

clean:
	rm -rf *.o
	rm -rf bootloader
	rm -rf boot.elf
	rm -rf $(DEPDIR)
