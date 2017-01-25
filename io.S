	;; Utility I/O functions for bootloader
	;; Functions here are meant to be called from C/C++
bits 32
%macro FUNC 1
global %1
%1:
%endmacro
	;; char inb(uint16_t port) read in one byte from port
FUNC inb
	push ebp
	mov ebp, esp
	mov dx, [ebp+0x8]
	xor eax, eax
	in  al, dx
	pop ebp
	ret
	;; outb(uint16_t port, uint8_t value)
	;; Write value to port
FUNC outb
	push ebp
	mov ebp, esp
	mov edx, [ebp+0x8]
	mov eax,[ebp+0x8+0x4]
	out dx, al
	pop ebp
	ret
	;; void insl(uint16_t port, void *dst, int count)
	;; Read count bytes from port and store them in dst
	;; count MUST be a multiple of four
FUNC insl
	push ebp
	mov ebp, esp
	push edi
	mov dx, [ebp+0x8]		; I/O Port
	mov edi, [ebp+0xC]		; Destination address
	mov ecx, [ebp+0x10]		; Byte count
	cld						; Increment edi address
	rep insd				; read in a double word ecx time
	pop edi
	pop ebp
	ret
;FUNC PrintString			; Low level print debugging, for before a tty is set up
;	push ebp
;	mov ebp, esp
;	mov ecx, [ebp+0x8]
;	mov edx, vmem
;PrintChar:
;	mov  al, [ecx]
;	test al, al
;	jz PrintCharExit
;	mov  ah, whiteonblack
;	mov  [edx], ax
;	add edx, 0x2
;	inc ecx
;	jmp PrintChar
;PrintCharExit:
;	pop ebp
;	ret
	;; Data
;vmem	 equ 0xb8000
;whiteonblack equ 0x0f
