#include <stdlib.h>
#include "heap.h"

/**
 * heap_delete - Deletes a heap
 * @heap: Pointer to the heap to delete
 * @free_data: Function to free the data stored in nodes
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
    if (!heap)
        return;

    (void)free_data;
    free(heap);
}
