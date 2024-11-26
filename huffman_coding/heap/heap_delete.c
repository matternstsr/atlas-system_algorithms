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
    for (size_t i = 0; i < heap->size; i++)
    {
        if (heap->array[i])
        {
            free_data(heap->array[i]->data);
            free(heap->array[i]);
        }
    }
    free(heap->array);
    free(heap);
}
