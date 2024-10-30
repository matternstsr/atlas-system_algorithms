#include "rb_trees.h"

/**
* array_to_rb_tree - Converts an array into a red-black tree.
* @array: PTR to array of integers.
* @size: Number of elements in array.
*
* Return: PTR to root of newly created red-black tree.
*/
rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	/* Initialize tree to NULL */
	rb_tree_t *tree = NULL;

	/* Insert each element of array into red-black tree */
	for (size_t i = 0; i < size; i++)
	{
		rb_tree_insert(&tree, array[i]); /* Insert current element */
	}

	/* Return PTR to root of tree */
	return (tree);
}
