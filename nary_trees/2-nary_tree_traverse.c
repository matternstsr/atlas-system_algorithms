#include <stdlib.h>
#include "nary_trees.h"

/**
* nary_tree_traverse - Trav an N-ary tree and applies an action on each node.
* @root: Pointer to root of tree.
* @action: Func to execute for each node, it takes node and depth as arguments.
* Return: maximum depth of tree.
*/
size_t nary_tree_traverse(nary_tree_t const *root,
							void (*action)(nary_tree_t const *node,
							size_t depth))
{
	size_t max_depth = 0;
	nary_tree_t const *child;

	if (!root || !action)
		return (0);
	/* Perform action on current node */
	action(root, 0);
	/* Traverse children */
	child = root->children;
	while (child)
	{
		/* Recursively traverse each child, increasing depth */
		size_t child_depth = nary_tree_traverse(child, action);
		if (child_depth > max_depth)
			max_depth = child_depth;
		child = child->next;
	}
	/* Return maximum depth encountered */
	return (max_depth + 1);
}
