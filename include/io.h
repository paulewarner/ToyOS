#ifndef TYPES_H

#define TYPES_H

#include "types.h"

char inb(uint16_t port);
void outb(uint16_t port, uint8_t value);
void insl(uint16_t port, void *dst, int count);

#endif /* TYPES_H */