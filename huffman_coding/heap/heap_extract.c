#include <stdlib.h>
#include "heap.h"

/**
* heap_extract - Extracts the root value from the Min Binary Heap
* @heap: Pointer to the heap to extract the value from
*
* Return: Pointer to the extracted value, or NULL if it fails
*
* Extract the root: As you've done, you extract the data at the root.
* Move the last node to the root: After extracting the root,
* move the last node to the root to keep the tree a complete binary tree.
* Bubble down the new root: After moving the last node to the root,
* you need to "bubble down" the node to restore the heap property.
* This means making sure the new root is smaller than its children
* and that the heap structure remains valid.
*
*/
void *heap_extract(heap_t *heap)
{
	void *data;
	binary_tree_node_t *last_node;

	if (!heap || !heap->root)
		return (NULL);

	data = heap->root->data;

	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
	}
	else
	{
		*last_node = heap->root;
		binary_tree_node_t *current = heap->root;
		binary_tree_node_t *queue[1024];
		int front = 0, rear = 0;

		queue[rear++] = current;

		while (front < rear)
		{
			current = queue[front++];
			if (current->left)
				queue[rear++] = current->left;
			if (current->right)
				queue[rear++] = current->right;
		}
		if (current != heap->root)
			heap->root->data = current->data;
		free(current);
		heap->root->left = NULL, heap->root->right = NULL;
	}
	heap->size--;
	bubble_down(heap->root, heap);

	return (data);
}
