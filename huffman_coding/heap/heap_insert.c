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
		binary_tree_node_t *current = heap->root;
		binary_tree_node_t *queue[1024];
		int front = 0, rear = 0;
		queue[rear++] = current;

		while (front < rear)
		{
			current = queue[front++];
			if (current->left == NULL)
			{
				current->left = node;
				node->parent = current;
				break;
			}
			else
			{
				queue[rear++] = current->left;
			}

			if (current->right == NULL)
			{
				current->right = node;
				node->parent = current;
				break;
			}
			else
			{
				queue[rear++] = current->right;
			}
		}
	}

	bubble_up(node, heap);

	heap->size++;
	return (node);
}
