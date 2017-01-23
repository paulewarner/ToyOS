
%macro SEG_NULLASM 0
	dq 0
%endmacro

; The 0xC0 means the limit is in 4096-byte units
; and (for executable segments) 32-bit mode.

; MYSEG(type, base, limit): macro to make my own x86 segment descriptors 
%macro SEG_ASM 3
	dw (((%3) >> 12) & 0xFFFF) 		; first part of segment limit
	dw ((%2) & 0xFFFF)		; first part of base address
	db (((%2) >> 16) & 0xFF) 	; next 8 bytes of base address
	db (0x90 | (%1)) 		; type and other description
	db (0xC0 | (((%3) >> 28) & 0xF))
	db (((%2) >> 24) & 0xFF)
%endmacro

%define STA_X     0x8       ; Executable segment
%define STA_E     0x4       ; Expand down (non-executable segments)
%define STA_C     0x4       ; Conforming code segment (executable only)
%define STA_W     0x2       ; Writeable (non-executable segments)
%define STA_R     0x2       ; Readable (executable segments)
%define STA_A     0x1       ; Accessed 
