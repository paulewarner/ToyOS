#include "multiboot.h"
#include "types.h"
#include "tty.h"
#include "vm.h"
#include "util.h"

extern void *mboot_info;
extern int mboot_magic;

extern void enable_paging(void);

void copy_mmap(struct multiboot_tag_mmap *mmap)
{
    struct multiboot_mmap_entry *entry;
    size_t n_entries = (mmap->size - sizeof(*mmap))/mmap->entry_size;
    for (entry = mmap->entries; entry - mmap->entries < n_entries; entry++) {
        if (entry->type == MULTIBOOT_MEMORY_AVAILABLE) {

        }
    }
}

int main()
{
    struct multiboot_tag *tag;
    tty_init();
    if (mboot_magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        panic("Incorrect magic multiboot number");
    }
    unsigned long l = (unsigned long)mboot_info;
    if (l & 7) {
        panic("Multiboot structure is unaligned");
    }
    printk("Hello!");
    for (tag = (struct multiboot_tag *) (l + 8);
         tag->type != MULTIBOOT_TAG_TYPE_END;
         tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag + ((tag->size + 7) & ~7))) {
        switch (tag->type) {
        case MULTIBOOT_TAG_TYPE_MMAP:
            copy_mmap((struct multiboot_tag_mmap *)tag);
            break;
        }
    }
}
