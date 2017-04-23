#define MAGIC 0xe85250d6

.globl .header_start
header_start:
    .int MAGIC
    .int 0
    .int header_end - header_start
    .int 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    .word 0
    .word 0
    .int 8
header_end: