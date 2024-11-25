#include <stdlib.h>
#include "heap.h"

/**
* heap_insert - Inserts a value in a Min Binary Heap
* @heap: Pointer to the heap to insert the node in
* @data: Data to be stored in the new node
*
* Return: Pointer to the new node, or NULL if it fails
*/
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *node;

	if (!heap || !data)
		return (NULL);

	node = binary_tree_node(NULL, data);
	if (!node)
		return (NULL);

	if (heap->root == NULL)
	{
		heap->root = node;
	}
	else
	{
	}

	heap->size++;
	return (node);
}
