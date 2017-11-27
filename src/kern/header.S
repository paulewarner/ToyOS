#define MAGIC 0xe85250d6

.globl .header_start
header_start:
    .long MAGIC  
    .long 0                                                          // x86 32 bit protected mode OS
    .long header_end - header_start                                  // Length of the header
    .long 0x100000000 - (0xe85250d6 + (header_end - header_start))   // Checksum value of the OS image
    // Tags
info_request_start:
    .word 1                                    // Tag type: Information request
    .word 0                                    // Flags: Non optional
    .int info_request_end - info_request_start // Size of the tag
    .int 6                                     // Request memory map
info_request_end:
    .balign 8
    // Termination tag
    .word 0
    .word 0
    .int 8
header_end: