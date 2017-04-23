	# Utility I/O functions for the kernel
	# Functions here are meant to be called from C/C++

	# char inb(uint16_t port) read in one byte from port
.globl inb
inb:
	mov %di, %dx
	xor %rax, %rax
	in %dx, %al
	ret
	# outb(uint16_t port, uint8_t value)
	# Write value to port
.globl outb
outb:
	mov %di, %dx
	mov $0xFF, %ax
	and %si, %ax
	out %al, %dx
	ret
	# void insl(uint16_t port, void *dst, int count)
	# Read count bytes from port and store them in dst
	# count MUST be a multiple of four
.globl insl
	push %rdi
	mov %di, %dx
	mov %rsi, %rdi
	mov %rdx, %rcx
	cld
	rep insl
	pop %rdi
	ret
