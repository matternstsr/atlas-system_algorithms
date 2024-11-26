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

/**
* symbol_compare - Compares two symbols by frequency.
* @a: The first symbol.
* @b: The second symbol.
* Return: Negative, zero, or positive value based on comparison.
*/
int symbol_compare(void *a, void *b)
{
	symbol_t *symbol_a = (symbol_t *)a;
	symbol_t *symbol_b = (symbol_t *)b;

	return ((int)(symbol_a->freq - symbol_b->freq));
}

/**
* binary_tree_node_create - Creates a binary tree node.
* @data: The data to store in the node.
* Return: A pointer to the newly created node.
*/
binary_tree_node_t *binary_tree_node_create(void *data)
{
	binary_tree_node_t *node = malloc(sizeof(binary_tree_node_t));

	if (!node)
		return (NULL);

	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return (node);
}

/**
* heap_destroy - Destroys the heap and frees all memory.
* @heap: The heap to destroy.
*/
void heap_destroy(heap_t *heap)
{
	if (!heap)
		return;
	free_heap_nodes(heap->root);
	free(heap);
}

/**
* free_heap_nodes - Recursively frees the nodes in the heap.
* @node: The current node to free.
*/
void free_heap_nodes(binary_tree_node_t *node)
{
	if (!node)
		return;
	free_heap_nodes(node->left);
	free_heap_nodes(node->right);
	if (node->data)
		free(node->data);
	free(node);
}
