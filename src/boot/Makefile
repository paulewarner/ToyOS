AS = nasm
CFLAGS += -fno-stack-protector -static -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -O -fno-pic -nostdinc -m32 $(INC)
ASFLAGS += $(INC)/ -f elf32

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
