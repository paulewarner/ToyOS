CFLAGS += -g -fno-stack-protector -static -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -fno-pic -nostdinc $(INC)
ASFLAGS += $(INC)/ -f elf64

DEPDIR = .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
COMPILE.S = $(AS) $(ASFLAGS) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

KERNSRCS = main.o \
		   io.o \
		   tty.o \
		   header.o \
		   entry.o \
		   vm.o \
		   util.o \

kernel: $(KERNSRCS) kernel.ld
	$(LD) -e start -n -T kernel.ld -o kernel $(KERNSRCS)

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
	rm -rf kernel
	rm -rf $(DEPDIR)

