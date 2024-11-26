#include <stdlib.h>
#include "heap.h"

/**
* heap_create - Creates a new heap
* @data_cmp: Function to compare two nodes
*
* Return: A pointer to the new heap, or NULL if it fails
*/
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *heap;

	heap = calloc(1, sizeof(heap_t));
	if (!heap)
		return (NULL);
	heap->size = 0;
	heap->root = NULL;
	heap->data_cmp = data_cmp;
	return (heap);
}