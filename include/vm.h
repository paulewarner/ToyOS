#ifndef VM_H
#define VM_H

#include "types.h"

#define PAGEDIR_NENTRIES 512

#define PAGE_PRESENT       (1 << 0)
#define PAGE_WRITE         (1 << 1)
#define PAGE_READ          (0)
#define PAGE_USER          (1 << 2)
#define PAGE_WRITE_THROUGH (1 << 3)
#define PAGE_CACHE_DISABLE (1 << 4)
#define PAGE_ACCESSED      (1 << 5)

#define PAGE_BIGPAGE       (1 << 7)

#define PAGE_ADDR_MASK     0xFFFFF000
#define PAGE_SIZE          0x1000
#define PAGE_BIGPAGE_SIZE  (PAGE_SIZE*PAGEDIR_NENTRIES)

void lcr3(uint64_t val);
uint64_t rcr3();


void kalloc_init(void);



#endif /* VM_H */