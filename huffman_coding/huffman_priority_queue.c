#include <stdlib.h>
#include "huffman.h"


/**
* huffman_priority_queue - Makes priority queue (min heap) for Huffman coding.
* @data: An array of characters to be used in Huffman coding.
* @freq: An array of frequencies associated with each character in @data.
* @size: The number of elements in the @data and @freq arrays.
* Return: A pointer to the created priority queue (min heap) containing nodes
*         for each symbol, or NULL if memory allocation fails or an error
*         occurs during the creation or insertion process.
*/
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue = heap_create(symbol_compare);

	if (!priority_queue)
		return (NULL);
	for (size_t i = 0; i < size; i++)
	{
		symbol_t *symbol = symbol_create(data[i], freq[i]);
		if (!symbol)
		{
			heap_destroy(priority_queue);
			return (NULL);
		}
		binary_tree_node_t *node = binary_tree_node_create(symbol);
		if (!node)
		{
			heap_destroy(priority_queue);
			return (NULL);
		}
		if (heap_insert(priority_queue, node) == 0)
		{
			heap_destroy(priority_queue);
			return (NULL);
		}
	}
	return (priority_queue);
}
