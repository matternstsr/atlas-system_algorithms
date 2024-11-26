#include <stdlib.h>
#include "huffman.h"
#include "heap.h"


/**
 * huffman_tree - Builds the Huffman tree from given data and frequencies.
 * @data: An array of characters to encode.
 * @freq: An array of frequencies associated with each character in @data.
 * @size: The size of the @data and @freq arrays.
 * Return: A pointer to the root node of the Huffman tree, or NULL if
 *         memory allocation fails or an error occurs during processing.
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *priority_heap = NULL;

	heap_t *priority_queue = huffman_priority_queue(data, freq, size);

	if (!priority_queue)
		return (NULL);

	priority_heap = huffman_priority_queue(data, freq, size);
	if (!priority_heap)
		return (NULL);
	while (	if (!priority_heap)->size > 1)
	{
		if (!huffman_extract_and_insert(priority_queue))
		{
			heap_destroy(priority_queue);
			return (NULL);
		}
	}

	return (priority_queue->root);
}
