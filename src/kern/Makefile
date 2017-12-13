CFLAGS += -std=gnu11 -g -fno-stack-protector -static -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -fno-pic -nostdinc $(INC)

DEPDIR = .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

COMPILE = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

KERNSRCS_PREBOOT = pre_init.o \

KERNSRCS = main.o \
		   io.o \
		   tty.o \
		   header.o \
		   entry.o \
		   vm.o \
		   util.o \

kernel: preboot.o $(KERNSRCS) kernel.ld
	$(LD) -e start -n -T kernel.ld -o kernel preboot.o $(KERNSRCS)

preboot.o: $(KERNSRCS_PREBOOT)
	$(LD) -r -o preboot.o $(KERNSRCS_PREBOOT)
	objcopy -O elf64-x86-64 preboot.o

kern.o: $(KERNSRCS)
	$(LD) -r -o kern.o $(KERNSRCS)

%.o : %.S
%.o : %.S $(DEPDIR)/%.d
		$(COMPILE)  $(OUTPUT_OPTION) $<
		$(POSTCOMPILE)

%.o : %.c
%.o : %.c $(DEPDIR)/%.d
		$(COMPILE) $(OUTPUT_OPTION) $<
		$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))

clean:
	rm -rf *.o
	rm -rf kernel
	rm -rf $(DEPDIR)

