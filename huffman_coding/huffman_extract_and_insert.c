#include <stdlib.h>
#include "huffman.h"

/**
* huffman_extract_and_insert - Extracts two least frequent nodes from
* priority queue & inserts a new internal node with sum of their frequencies.
* @priority_queue: A pointer to priority queue (min heap) from which nodes
*                  will be extracted and into which new node will be inserted.
* Return: 1 on success, 0 on failure.
*/
int huffman_extract_and_insert(heap_t *priority_queue)
{
	if (!priority_queue || !priority_queue->root)
		return (0);
	binary_tree_node_t *node1 = heap_extract(priority_queue);
	binary_tree_node_t *node2 = heap_extract(priority_queue);

	if (!node1 || !node2)
		return (0);
	symbol_t *symbol1 = (symbol_t *)node1->data;
	symbol_t *symbol2 = (symbol_t *)node2->data;
	symbol_t *new_symbol = symbol_create('\0', symbol1->freq + symbol2->freq);

	if (!new_symbol)
		return (0);
	binary_tree_node_t *new_node = binary_tree_node_create(new_symbol);

	if (!new_node)
		return (0);
	new_node->left = node1;
	new_node->right = node2;
	if (heap_insert(priority_queue, new_node) == 0)
		return (0);

	return (1);
}
