ENTRY(start)
UNPAGED_BEGIN = 1M;
PAGED_BEGIN = 0xc0000000;
OFFSET = PAGED_BEGIN - UNPAGED_BEGIN;

SECTIONS {
    . = UNPAGED_BEGIN;

    .boot :
    {
        *(.multiboot_header)
    }

    .text : 
    {
        *(.text)
    }
	.data ALIGN(4096) :
    {
        *(.data .rodata*)
    }
	.bss  ALIGN(4096) :
    { 
        *(.bss COMMON)
    }

    . += OFFSET;
    PROVIDE(unpaged_end = .);

	.unpaged_text :
    {
        preboot.o(.text)
    }
	.unpaged_data ALIGN(4096) :
    {
        preboot.o(.data .rodata*)
    }
	.unpaged_bss  ALIGN(4096) :
    { 
        preboot.o(.bss COMMON)
    }

    PROVIDE(end = .);
}