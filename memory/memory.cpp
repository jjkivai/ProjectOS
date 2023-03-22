#include "memory.h"

void *alloc (size_t size)
{
    int *ptr = (int *) malloc (size * sizeof(int));
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


