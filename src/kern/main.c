#include "multiboot.h"
#include "types.h"
#include "tty.h"
#include "vm.h"
#include "util.h"

extern void *mboot_info;
extern int mboot_magic;

extern void enable_paging(void);

static uint64_t p4_table[PAGEDIR_NENTRIES] __attribute__ ((aligned(4096)));
/* P3 table */
static uint64_t p3_table[PAGEDIR_NENTRIES] __attribute__ ((aligned(4096)));
/* P2 tables */
static uint64_t p2_table[PAGEDIR_NENTRIES] __attribute__ ((aligned(4096)));

void copy_mmap(struct multiboot_tag_mmap *mmap)
{
    struct multiboot_mmap_entry *entry;
    size_t n_entries = (mmap->size - sizeof(*mmap))/mmap->entry_size;
    for (entry = mmap->entries; entry - mmap->entries < n_entries; entry++) {
        if (entry->type == MULTIBOOT_MEMORY_AVAILABLE) {

        }
    }
}

uint64_t build_pg_table()
{
    uint64_t pde = 0;
    uint64_t addr;
    uint64_t flags = PAGE_PRESENT | PAGE_BIGPAGE | PAGE_WRITE;
    p4_table[0] = ((uint64_t)&p3_table | 0x3);
    p3_table[0] = ((uint64_t)&p2_table | 0x3);
    uint64_t page = 0;
    for (pde = 0; pde < PAGEDIR_NENTRIES; pde += 2) {
        addr = PAGE_BIGPAGE_SIZE*page++;
        p2_table[pde] = addr | flags;
        p2_table[pde+1] = 0;
        // for (pde = 0; pde < PAGEDIR_NENTRIES; pde++) {
        //     flags = PAGE_PRESENT | PAGE_BIGPAGE | PAGE_WRITE;
        //     addr = pde*PAGE_BIGPAGE_SIZE;
        //     pagetables[pte][pde] = flags | addr;
        // }
    }
    return pde;
}

int main()
{
    tty_init();
    uint64_t new_pgtable = build_pg_table();
    uint64_t pgtable = rcr3();
    lcr3((uint64_t)p4_table);
    printk("Replaced pgtable at %#x with %#x", p4_table, p4_table[0]);
    // if (mboot_magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
    //     panic("Incorrect magic multiboot number");
    // }
    // unsigned long l = (unsigned long)mboot_info;
    // if (l & 7) {
    //     panic("Multiboot structure is unaligned");
    // }
    // for (struct multiboot_tag *tag = (struct multiboot_tag *) (l + 8);
    //      tag->type != MULTIBOOT_TAG_TYPE_END;
    //      tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag + ((tag->size + 7) & ~7))) {
    //     switch (tag->type) {
    //     case MULTIBOOT_TAG_TYPE_MMAP:
    //         copy_mmap((struct multiboot_tag_mmap *)tag);
    //         break;
    //     }
    // }
}
