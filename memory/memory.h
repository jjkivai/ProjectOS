#pragma once
#include <stdint.h>
#include <stddef.h>
#include "../drivers/display.h"

namespace memory {
    struct memory_block;
    void *alloc (int size);

    void *malloc (size_t size);

    void *realloc (uint8_t *ptr, size_t size);

    void free (void *ptr);

    void mem_copy (uint8_t *dest, uint8_t *src, uint32_t size);

    void init_memory();
    void print_memory(Display &display);
    void print_dynamic_memory(Display &display);
    }

