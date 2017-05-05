#include "multiboot.h"
#include "types.h"
#include "tty.h"
#include "vm.h"
#include "util.h"

extern struct multiboot_info *kinfo;

extern void enable_paging(void);

int main()
{
    tty_init();
    if (kinfo->flags & MULTIBOOT_MMAP) {
        printk("Have memory map");
    } else {
        printk("No mem map");
    }
}
