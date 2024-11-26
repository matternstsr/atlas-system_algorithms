#include <stdlib.h>
#include "heap.h"

/**
* insert_node - Inserts a new node into the heap at the correct position
* @heap: Pointer to the heap to insert the node in
* @data: Data to be stored in the new node
*
* Return: Pointer to the new node, or NULL if it fails
*/
binary_tree_node_t *insert_node(heap_t *heap, void *data)
{
	binary_tree_node_t *node;
	binary_tree_node_t *current;
	binary_tree_node_t *queue[1024];
	int front = 0, rear = 0;

	if (!heap || !data)
		return (NULL);

	node = binary_tree_node(NULL, data);
	if (!node)
		return (NULL);

	if (heap->root == NULL)
		heap->root = node;
	else
	{
		current = heap->root, queue[rear++] = current;

		while (front < rear)
		{
			current = queue[front++];

			if (current->left == NULL)
			{
				current->left = node, node->parent = current;
				break;
			}
			else
				queue[rear++] = current->left;

			if (current->right == NULL)
			{
				current->right = node, node->parent = current;
				break;
			}
			else
				queue[rear++] = current->right;
		}
	}
	return (node);
}

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

	node = insert_node(heap, data);
	if (!node)
		return (NULL);

	bubble_up(node, heap);
	heap->size++;
	return (node);
}
