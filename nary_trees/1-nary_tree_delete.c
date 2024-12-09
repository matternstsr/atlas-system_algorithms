the #include <stdlib.h>
#include "nary_trees.h"

/**
* nary_tree_delete - Deletes an entire N-ary tree.
* @tree: Pointer to the root node of the tree to be deleted.
*/
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *temp;

	if (!tree)
		return;
	/* Recursively delete each child */
	while (tree->children)
	{
		temp = tree->children;
		tree->children = tree->children->next;   /* Move to the next child */
		nary_tree_delete(temp);   /* Recursively delete the child */
	}
	/* Free the content of the node */
	free(tree->content);
	/* Free the node itself */
	free(tree);
}
