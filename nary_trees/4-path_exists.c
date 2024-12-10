#include "nary_trees.h"

/**
* path_exists_helper - Recursive helper function to check if a path exists
* @node: The current node to check
* @path: The array of strings representing the path
* @index: The current index in the path
* Return: 1 if the path exists, otherwise 0
*/
int path_exists_helper(nary_tree_t const *node,
						char const * const *path, size_t index)
{
	if (path[index] == NULL) /* If we've reached the end of the path */
		return (1); /* Path exists successfully */
	if (node == NULL) /* If node is NULL, path does not exist */
		return (0);

	/* Search for the child node that matches the current path element */
	nary_tree_t const *child = node->children;

	while (child)
	{
		if (strcmp(child->content, path[index]) == 0)
			/* If found, continue with the next node in the path */
			return (path_exists_helper(child, path, index + 1));
		child = child->next;
	}
	/* If no matching child is found */
	return (0);
}
/**
* path_exists - Checks if a given path exists in the N-ary tree
* @root: The root of the N-ary tree
* @path: The NULL-terminated array of strings representing the path
* Return: 1 if the path exists, otherwise 0
*/
int path_exists(nary_tree_t const *root, char const * const *path)
{
	if (root == NULL || path == NULL || path[0] == NULL)
		return (0);
	return (path_exists_helper(root, path, 0));
}
