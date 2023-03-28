#include "memory.h"


#define MEMORY_TOTAL_SIZE 0x1000
#define MEMORY_BLOCK_SIZE sizeof(memory::memory_block)

namespace memory
{
    // void *alloc (int size);
    // //void free (void *ptr);
    // void *malloc(size_t size);
    // void *find_free_block(memory_block *new_block, size_t size);

    void *alloc (int size)
    {
        int *ptr = (int *) memory::malloc(size * sizeof(int));
        if (ptr == NULL)
        {
            return NULL;
        }
        for (int i = 0; i < size; i++)
        {
            ptr[i] = 0;
        }
        return ptr;
    }

    struct __attribute__((packed)) memory_block {
        uint32_t size;
        uint32_t magic;
        bool free;
        struct memory_block *next;
        struct memory_block *prev;
    };

    static uint8_t dynamic_memory_area[MEMORY_TOTAL_SIZE];
    static memory_block *first_block;

    void *find_free_block(memory_block *new_block, size_t size) {
        memory_block *free_block = (memory_block *) NULL;
        uint32_t free_block_size = MEMORY_TOTAL_SIZE + 1;

        memory_block *current_block = new_block;

        while(current_block != NULL) {
            if((current_block->free) && 
            (current_block->size >= (size + MEMORY_BLOCK_SIZE)) && 
            (current_block->size <= free_block_size)) {

                free_block = current_block;
                free_block_size = current_block->size;
            }
            current_block = current_block->next;
        }

        return free_block;
    }


    void *malloc (size_t size)
    {
        memory_block *free_block = (memory_block *) find_free_block(first_block, size);

        if(free_block != NULL) {
            free_block->size = free_block->size - size - MEMORY_BLOCK_SIZE;
            free_block->magic = 0x12345678;
            memory_block *new_block = (memory_block *) (((uint8_t *) free_block) + MEMORY_BLOCK_SIZE + free_block->size);
            new_block->size = size;
            new_block->free = false;
            new_block->magic = 0x12345678;
            new_block->next = free_block->next;
            new_block->prev = free_block;

            if(free_block->next != NULL) {
                free_block->next->prev = new_block;
            }

            free_block->next = new_block;

            return (void *) (((uint8_t *) new_block) + MEMORY_BLOCK_SIZE);
        }

        return NULL;
    }

    void *realloc (uint8_t *ptr, size_t size)
    {
        memory_block *block = (memory_block *) (((uint8_t *) ptr) - MEMORY_BLOCK_SIZE);
        if(block->magic != 0x12345678) {
            return NULL;
        }

        if(block->size >= size) {
            return ptr;
        }

        uint8_t *new_ptr = (uint8_t*)malloc(size);
        if(new_ptr == NULL) {
            return NULL;
        }

        mem_copy(new_ptr, ptr, block->size);
        free(ptr);

        return new_ptr;

    }

    void mem_copy (uint8_t *dest, uint8_t *src, uint32_t size)
    {

        for(int i = 0; i < size; i++) {
            *(dest + 1) = *(src + 1);
        }

    }

    void free (void *ptr)
    {
        if(ptr == NULL) {
            return;
        }
        memory_block *block = (memory_block *) (((uint8_t *) ptr) - MEMORY_BLOCK_SIZE);
        if(block->magic != 0x12345678) {
            return;
        }

        block->free = true;

        // Merge with next block
        if(block->next != NULL && block->next->free) {
            block->size += MEMORY_BLOCK_SIZE + block->next->size;
            block->next = block->next->next;
            if(block->next != NULL) {
                block->next->prev = block;
            }
        }
        // Merge with previous block
        if(block->prev != NULL && block->prev->free) {
            block->prev->size += MEMORY_BLOCK_SIZE + block->size;
            block->prev->next = block->next;
            if(block->next != NULL) {
                block->next->prev = block->prev;
            }
        }
    }

    void init_memory()
    {
        first_block = (memory_block *) dynamic_memory_area;
        first_block->size = MEMORY_TOTAL_SIZE - MEMORY_BLOCK_SIZE;
        first_block->free = true;
        first_block->magic = 0x12345678;
        first_block->next = NULL;
        first_block->prev = NULL;
    }
    void print_memory(Display &display) {
        char node_size[256];
        int_to_string(MEMORY_BLOCK_SIZE, node_size);
        display.print_screen("Node size: ");
        display.print_screen(node_size);
        display.print_newline();
    }
    void print_dynamic_memory(Display &display) {
        memory_block *current_block = first_block;
        display.print_screen("Dynamic memory: [");
        while(current_block != NULL) {
            char node_size[256];
            int_to_string(current_block->size, node_size);
            display.print_screen("{size= ");
            display.print_screen(node_size);
            char free[256];
            int_to_string(!(current_block->free), free);
            display.print_screen(";used = ");
            display.print_screen(free);
            display.print_screen("};");
            current_block = current_block->next;
        }
        display.print_screen("]");
        display.print_newline();
    }
}