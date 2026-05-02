#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

// =====================
// Core API
// =====================
void init_allocator(size_t size);
void* allocate(size_t size);
void deallocate(void* ptr);


// =====================
// Debug helpers (optional but recommended)
// =====================
void print_memory_layout(void);

// =====================
// Internal block structure (exposed for now for simplicity)
// Can be hid later in .c
// =====================
typedef struct block {
    size_t size;
    int free;
    struct block* next;
} block_t;

#endif
