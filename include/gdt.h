
#define STA_X     0x8       // Executable segment
#define STA_E     0x4       // Expand down (non-executable segments)
#define STA_C     0x4       // Conforming code segment (executable only)
#define STA_W     0x2       // Writeable (non-executable segments)
#define STA_R     0x2       // Readable (executable segments)
#define STA_A     0x1       // Accessed 


#define SEG_NULLASM \
	.word 0, 0;     \
	.byte 0, 0, 0, 0

// The 0xC0 means the limit is in 4096-byte units
// and (for executable segments) 32-bit mode.

// SEG(type, base, limit, is64): macro to make my own x86 segment descriptors                                                                                                                   
#define SEG(type,base,lim)                                      \
        .word (((lim) >> 12) & 0xffff), ((base) & 0xffff);      \
        .byte (((base) >> 16) & 0xff), (0x90 | (type)),         \
                (0xC0 | 1 << 5 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xff)


// #define SEG(type, base, limit, is64)      \
// 	.word  (((limit) >> 12) & 0xFFFF);    \
// 	.word  ((base) & 0xFFFF);             \
// 	.byte  (((base) >> 16) & 0xFF);       \
// 	.byte (0x90 | (type));                \
//     .byte ((1 << 5) | ((limit >> 28) & 0xF));  \
// 	.byte (((base) >> 24) & 0xFF);