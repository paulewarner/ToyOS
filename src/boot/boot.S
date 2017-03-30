bits 16						; Tells the assembler that its a 16 bit code
%include "gdt.S"			; be in memory after it is been loaded
global start
extern LoadStage2
start:
	cli 					; disable interrupt flag
	mov sp, 0x7BFF 			; Set a temporary stack we can use, 30 KiB
;	xor ax, ax 				; Zero out data segment registers
;	mov ds, ax
;	mov es, ax
;	mov ss, ax
	lgdt [gdt.pointer]		; load GDT
	mov eax, cr0			; Set the Protection Enable bit
	or eax, 0x1
	mov cr0, eax
	jmp gdt.code:EnterC		; Start executing 32-bit code

;EnableA20:					; Procedure to enable the A20 line
;	call CheckA20
;	test ax, ax 			; Test ax against itself to see if it's zero
;	jnz enablea20_ret 		; If it is, then we can leave now
;	call EnableA20Bios 		; First test for BIOS functions
;	test ax, ax
;	jnz enablea20_ret
;	call EnableA20Keyboard
;	test ax, ax
;	jnz enablea20_ret
;	hlt						; We're fucked, freeze
;enablea20_ret:
;	ret
;CheckA20:		   			; Procedure to check the status of the A20 line
;	xor ax, ax	   			; set ax to zero
;	mov es, ax 				; set es to zero
;	not ax 					; set ax to 0xFFFF, last possible addressable line
;	mov ds, ax				; set ds to 0xFFFF as well
;	mov di, 0x0500 			; set di to 0x0500
;	mov si, 0x0510 			; set si to 0x0510
;	mov al, byte [es:di]    ; into al the byte at es:di (0x00000500)
;	push ax 				; keep it for later
;	mov al, byte [ds:si] 	; now get the byte at ds:si (0xFFFF0510)
;	push ax 				; now store that for later
;	mov byte [es:di], 0x00 	; Move zero into the first location we copied
;	mov byte [ds:si], 0xFF 	; But move 0xFF into the second
;
;	cmp byte [es:di], 0xFF	; See if the first location has changed
;	pop ax					; get the first old byte back
;	mov byte [ds:si], al   	; ...and store the first old byte wherever it was
;	pop ax     				; now get the second old byte
;	mov byte [es:di], al 	; ... and put it back where we found it
;	mov ax, 0				; set our return to be zero...
;	je checka20_exit		; and return that if the two were equal
;	mov ax, 1 				; otherwise, return 1 to show the line was enabled
;checka20_exit:
;	ret
;EnableA20Bios:				; Procedure that attempts to use bios to enable A20 line
;	mov ax, 0x2403 			; Code for the the A20 gate support
;	int 0x15				; do the BIOS interrupt
;	jb a20bios_fail 		; No support for this interrupt
;	cmp ah, 0				; check if the function returned 0
;	jnz a20bios_fail		; A20 BIOS functions not supported, boo =-(
;
;	mov ax, 0x2401  		; Code for activation of the A20 gate
;	int 0x15
;	jb a20bios_fail
;	cmp ah, 0
;	jnz a20bios_fail 		; Couldn't enable A20 gate
;	mov ax, 1				; It worked! Hooray!
;	jmp a20bios_exit
;a20bios_fail:
;	mov ax, 1
a20bios_exit:
;	ret
;EnableA20Keyboard:	   		; Procedure to enable the A20 gate using the keyboard controller
;a20kbd_part1:
;	in al, 0x64 			; wait for the controller to be not busy
;	test al, byte 0x2 		; test if we got something back
;	jnz a20kbd_part1 		; If we did, then we need to wait a little longer
;	mov al, 0xd1
;	out 0x64, al 			; send the message on I/O port 0x64
;a20kbd_part2:
;	in al, 0x64 			; wait some more
;	test al, byte 0x2
;	jnz a20kbd_part2
;
;	mov al, 0xdf
;	out 0x60, al 			; now send the message to enable the A20 line
;	mov ax, 1 				; Function should always succeed I hope...
;	ret
;DisableA20:		    		; Procedure to disable the A20 gate, for testing purposes
;	mov ax, 0x2400 			; Code to disable A20 gate
;	int 0x15
;	jb a20disable_fail
;	cmp ah, 0
;	jnz a20disable_fail
;	mov ax, 1
;a20disable_fail:
;	mov ax, 0
;a20disable_ret:
;	ret
bits 32
EnterC:	 					; Procedure to begin running C code
	;; We need to load all code segments that might need to be used
	;; with the same data segment selector we used to the code segment
	;mov ax, gdt.code
	;mov ds, ax
	;mov es, ax
	;mov ss, ax
	;; Now zero the rest of them
	;xor ax, ax
	;mov fs, ax
	;mov gs, ax
	call LoadStage2
	hlt 					; unreachable, but hang anyway
	;; Data
gdt:
	SEG_NULLASM
.code: equ $ - gdt
	ASM (STA_X|STA_R), 0x0, 0xFFFFFFFF
.pointer:
	dw ($ - gdt - 1)
	dd gdt
