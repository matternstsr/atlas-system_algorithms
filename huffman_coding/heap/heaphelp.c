#include <stdlib.h>
#include "heap.h"

/**
* bubble_up - Bubbles a node up the heap to maintain heap property
* @node: The node to bubble up
* @heap: The heap structure containing the node
*/
void bubble_up(binary_tree_node_t *node, heap_t *heap)
{
	while (node->parent && heap->data_cmp(node->data, node->parent->data) < 0)
	{
		void *temp = node->data;

		node->data = node->parent->data;
		node->parent->data = temp;

		node = node->parent;
	}
}


/**
* bubble_down - Moves a node down the heap to restore heap property
* @node: The node to bubble down
* @heap: The heap structure containing the node
*/
void bubble_down(binary_tree_node_t *node, heap_t *heap)
{
	binary_tree_node_t *smallest = node;
	binary_tree_node_t *left = node->left;
	binary_tree_node_t *right = node->right;

	if (left && heap->data_cmp(left->data, smallest->data) < 0)
		smallest = left;
	if (right && heap->data_cmp(right->data, smallest->data) < 0)
		smallest = right;
	if (smallest != node)
	{
		void *temp = node->data;
		node->data = smallest->data;
		smallest->data = temp;
		bubble_down(smallest, heap);
	}
}
