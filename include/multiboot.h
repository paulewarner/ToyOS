#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include "types.h"


#define MULTIBOOT_MEM        (1 << 0)
#define MULTIBOOT_BOOTDEV    (1 << 1)
#define MULTIBOOT_CMDLINE    (1 << 2)
#define MULTIBOOT_MODS       (1 << 3)
#define MULTIBOOT_SYMS       ((1 << 4) | (1 << 5))
#define MULTIBOOT_MMAP       (1 << 6)
#define MULTIBOOT_DRIVES     (1 << 7)
#define MULTIBOOT_CONFIG     (1 << 8)
#define MULTIBOOT_BOOTLOADER (1 << 9)
#define MULTIBOOT_APM        (1 << 10)
#define MULTIBOOT_VBE        (1 << 11)

struct multiboot_info {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    uint32_t syms[4];
    uint32_t mmap_length;
    uint32_t mmap_addr;
    uint32_t drives_length;
    uint32_t drives_addr;
    uint32_t config_table;
    uint32_t boot_loader_name;
    uint32_t apm_table;
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint32_t vbe_mode;
    uint32_t vbe_interface_seg;
    uint32_t vbe_interface_off;
    uint32_t vbe_interface_len;
};

#endif /* MULTIBOOT_H */