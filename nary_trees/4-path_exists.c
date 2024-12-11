#include "nary_trees.h"

/**
* path_exists_helper - Recursive helper function to check if a path exists
* @node: The current node to check
* @path: The array of strings representing the path
* @index: The current index in the path
* Return: 1 if the path exists, otherwise 0
*/
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
	/* If we've reached the end of the path, return 1 (success) */
	if (path[index] == NULL)
		return (1);

	/* If node is NULL or path doesn't match, return 0 */
	if (node == NULL)
		return (0);

	/* If the current node matches the first element of the path, continue recursion */
	if (strcmp(node->content, path[index]) == 0)
	{
		/* If we've reached the last element in the path, check if it exists */
		if (path[index + 1] == NULL)
			return (1);
		/* Otherwise, recurse on children */
		nary_tree_t const *child = node->children;
		while (child)
		{
			/* Recur for the next node in the path */
			if (path_exists_helper(child, path, index + 1))
				return (1);
			child = child->next;
		}
	}
	/* If we did not find a match for the current node, return 0 */
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
