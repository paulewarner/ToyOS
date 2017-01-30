global start

%include "gdt.S"

section .text
bits 32
start:
    ; print `OK` to screen
    mov dword [0xb8000], 0x2f4b2f4f
    hlt
gdt:
	SEG_NULLASM
.code: equ $ - gdt
	SEG_ASM (STA_X|STA_R), 0x0, 0xFFFFFFFF
.pointer:
	dw ($ - gdt - 1)
	dd gdt

