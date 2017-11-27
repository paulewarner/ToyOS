#include "gdt.h"
.code32
.text
.globl start
.globl mboot_magic
.globl mboot_info
.globl p4_table
.globl p3_table
.globl p2_table
start:
    movl %eax, mboot_magic
    movl %ebx, mboot_info
    mov $stack_top, %esp
    # call setup_page_tables
    # call enable_paging
    call enable_fpu
    call enable_sse
    lgdt gdtdesc
    ljmp $(1<<3), $start_64
    hlt
setup_page_tables:
    # map first P4 entry to P3 table
    mov $p3_table, %eax
    or $0b11, %eax
    mov %eax, (p4_table)

    # map first P3 entry to P2 table
    mov $p2_table, %eax
    or $0b11, %eax
    mov %eax, (p3_table)

    # map each P2 entry to a huge 2MiB page
    mov $0, %ecx   # counter variable
map_p2_table:
    # map ecx-th P2 entry to a huge page that starts at the address (2MiB * ecx)
    mov $0x200000, %eax             # 2MiB
    mul %ecx                        # start adddress of ecx-th page
    or $0b10000011, %eax            # present + writable + huge
    mov %eax, p2_table(, %ecx, 8)   # map the entry
    inc %ecx                        # increase counter
    cmp $512, %ecx                  # if counter == 512, whole P2 table is mapped
    jne map_p2_table                # else map the next entry

    ret
enable_paging:
    # load P4 to cr3 register (cpu uses this to access P4 table)
    mov $p4_table, %eax
    mov %eax, %cr3

    # enable PAE flag in cr4 (Physical Address Extension)
    mov %cr4, %eax
    or $(1 << 5), %eax
    mov %eax, %cr4

    # set the long mode bit in the EFER MSR (model specific register)
    mov $0xC0000080, %ecx
    rdmsr
    or $(1 << 8), %eax
    wrmsr

    # enable paging in the cr0 register
    mov %cr0, %eax
    or $(1 << 31), %eax
    mov %eax, %cr0

    ret
enable_sse:
    mov $1, %eax
    cpuid
    test $(1 << 25), %edx     # check if SSE bit is enabled
    jz no_sse
    mov %cr0, %eax
    and $0xFFFB, %ax        # clear cr0.em bit
    or $2, %ax
    mov %eax, %cr0
    or $2, %ax
    mov %eax, %cr0
    mov %cr4, %eax
    or $(3 << 9), %ax          # enable SSE instructions and unmasked exceptions
    mov %eax, %cr4
    ret
no_sse:
    hlt
.globl enable_fpu
.set cr0_em, 0x2 # emulate the effect of an fpu in software. 
.set cr0_ts,  0x4 # Should the state of the fpu be saved on interrupt?
fpu_testword:
    .int 0x55AA
enable_fpu:
    # first, we test if process has an FPU by telling the processor to emulate the effect
    # of one in software (so that trying an operation won't cause an interrupt), then
    # testing to see if our test word has been overwritten
    mov %cr0, %edx
    mov %edx, %ecx
    and $((-1) - (cr0_em + cr0_ts)), %edx
    mov %edx, %cr0
    fninit
    fnstsw (fpu_testword)
    cmpl $0, (fpu_testword)
    jne nofpu
    mov %ecx, %cr0
    fninit
    ret
nofpu:
    hlt
.code64
.globl start_64
start_64:
    call main
    hlt          # not reached
.p2align 2
gdt:
    SEG_NULLASM
gdt_seg1:
    SEG(STA_X|STA_R, 0x0, 0xFFFFFFFF)
gdt_seg2:
    SEG(STA_X, 0x0, 0xFFFFFFFF)
gdtdesc:
    .word (gdtdesc - gdt - 1)
    .int gdt
mboot_info:
    .quad 0
mboot_magic:
    .long 0
.section .bss
.balign 4096
p4_table: .space 4096
p3_table: .space 4096
p2_table: .space 4096
stack_bottom: .space 128
stack_top:
