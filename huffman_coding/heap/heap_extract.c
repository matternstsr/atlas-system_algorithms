#include <stdlib.h>
#include "heap.h"

/**
* heap_extract - Extracts the root value from the Min Binary Heap
* @heap: Pointer to the heap to extract the value from
*
* Return: Pointer to the extracted value, or NULL if it fails
*/
void *heap_extract(heap_t *heap)
{
	void *data;

	if (!heap || !heap->root)
		return (NULL);

	data = heap->root->data;

	heap->size--;
	return (data);
}
