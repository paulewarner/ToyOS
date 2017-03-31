
%macro SEG_NULLASM 0
	dq 0
%endmacro

; The 0xC0 means the limit is in 4096-byte units
; and (for executable segments) 32-bit mode.

; SEG(type, base, limit, is64): macro to make my own x86 segment descriptors 
%macro SEG 4
	dw (((%3) >> 12) & 0xFFFF) 		; first part of segment limit
	dw ((%2) & 0xFFFF)				; first part of base address
	db (((%2) >> 16) & 0xFF) 		; next 8 bytes of base address
	db (0x90 | (%1)) 				; Access control byte
	%if %4
	db ((%4 << 5) | ((%3 >> 28) & 0xF)) ; Flags and limit register
	%else
	db (0xC0 | (((%3) >> 28) & 0xF))
	%endif
	db (((%2) >> 24) & 0xFF)		; Last segment of the base address
%endmacro

%define STA_X     0x8       ; Executable segment
%define STA_E     0x4       ; Expand down (non-executable segments)
%define STA_C     0x4       ; Conforming code segment (executable only)
%define STA_W     0x2       ; Writeable (non-executable segments)
%define STA_R     0x2       ; Readable (executable segments)
%define STA_A     0x1       ; Accessed 

; PGTABLE base, flags 
; Create a page table with the given flags, starting at the given base
%macro PGTABLE 2
    %assign i (%2)/4096
    %rep 512
    dq ((%1) | (i << 12))
    %assign i i+1
    %endrep
%endmacro


%define PTE_PRESENT      0x001 ; Page is currently in memory
%define PTE_WRITABLE     0x002 ; Page is writable
%define PTE_USER         0x004 ; Page is owned by the user
%define PTE_WRITETHROUGH 0x008 ; Google it later
%define PTE_CACHEDISABLE 0x010 ; Disable caching on this page
%define PTE_ACCESSED     0x020 ; Has this page been accessed?
%define PTE_DIRTY        0x040 ; Has this page been written to?
%define PTE_PAGESIZE     0x080 ; What is the size of this page?
%define PTE_
%define PTE_COW          0x512 ; Is the page a COW page?