	;; Utility I/O functions for the kernel
	;; Functions here are meant to be called from C/C++
%macro FUNC 1
global %1
%1:
%endmacro
	;; char inb(uint16_t port) read in one byte from port
FUNC inb
    mov dx, di
    xor rax, rax
    in al, dx
    ret
	;; outb(uint16_t port, uint8_t value)
	;; Write value to port
FUNC outb
    mov dx, di
    ;; Need a mask to get lower 8 bytes of rsi
    mov ax, 0xFF
    and ax, si
    out dx, al
	ret
	;; void insl(uint16_t port, void *dst, int count)
	;; Read count bytes from port and store them in dst
	;; count MUST be a multiple of four
FUNC insl
	push rdi
    mov dx, di
    mov rdi, rsi
    mov rcx, rdx
	cld						; Increment rdi address
	rep insd				; read in a double word rcx times
	pop rdi
	ret
