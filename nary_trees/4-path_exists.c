#include "nary_trees.h"

/**
* path_exists_helper - Recursive helper function to check if a path exists
* @node: current node to check
* @path: array of strings representing path
* @index: current index in path
* Return: 1 if path exists, otherwise 0
*/
int path_exists_helper(nary_tree_t const *node,
						char const * const *path, size_t index)
{
	/* If we've reached end of path, return 1 (success) */
	if (path[index] == NULL)
		return (1);

	/* If node is NULL or path doesn't match, return 0 */
	if (node == NULL)
		return (0);

	/* If current node matches first element of path, continue recursion */
	if (strcmp(node->content, path[index]) == 0)
	{
		/* If we've reached last element in path, check if it exists */
		if (path[index + 1] == NULL)
			return (1);
		/* Otherwise, recurse on children */
		nary_tree_t const *child = node->children;

		while (child)
		{
			/* Recur for next node in path */
			if (path_exists_helper(child, path, index + 1))
				return (1);
			child = child->next;
		}
	}
	/* If we did not find a match for current node, return 0 */
	return (0);
}



/**
* path_exists - Checks if a given path exists in N-ary tree
* @root: root of N-ary tree
* @path: NULL-terminated array of strings representing path
* Return: 1 if path exists, otherwise 0
*/
int path_exists(nary_tree_t const *root, char const * const *path)
{
	if (root == NULL || path == NULL || path[0] == NULL)
		return (0);
	return (path_exists_helper(root, path, 0));
}
