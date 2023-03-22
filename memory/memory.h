#pragma once
#include <stdint.h>
#include <stddef.h>


void *alloc (size_t size);

void *malloc (size_t size);

void *realloc (void *ptr, size_t size);

void free (void *ptr);

void mem_copy (void *dest, void *src, size_t size);

