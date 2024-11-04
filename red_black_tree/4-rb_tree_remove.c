#include "rb_trees.h"
#include "4-rotations.c"
#include "Process.c"
/**
* rb_tree_remove - Removes a value from red-black tree.
* @root: PTR to root of red-black tree.
* @n: Value to be removed from tree.
*
* Return: PTR to root of modified tree.
*/
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n)
{
	/* Remove node containing value n from BST */
	rb_tree_t *node = bst_remove(root, n);

	if (!node)
		return (root); /* Return root if node was not found */

	/* Fix tree to maintain Red-Black properties after removal */
	return ((fix_remove)(root, node));
}

/**
* bst_remove - Removes a node with a specified value from the red-black tree.
* @root: PTR to the root of the tree.
* @n: Value of the node to be removed.
*
* Return: PTR to the new root of the tree, or NULL if the node was not found.
*/
rb_tree_t *bst_remove(rb_tree_t *root, int n)
{
	rb_tree_t *node = root;
	rb_tree_t *temp = NULL;

	while (node) /* Find node to be removed */
	{
		if (n < node->n)
			node = node->left;
		else if (n > node->n)
			node = node->right;
		else
			break; /* Node found */
	}
	if (!node)
		return (NULL); /* Node not found */
	if (node->left && node->right) /* Node has two children */
	{
		temp = node->right;
		while (temp->left)
			temp = temp->left;
		node->n = temp->n; /* Copy replacement's value to this node */
		node = temp; /* Prepare to remove the replacement */
	} /* Node has at most one child */
	rb_tree_t *child = (node->left) ? node->left : node->right;

	if (!child) /* Remove node and handle case of root */
	{
		if (node->color == BLACK) /* Node is a leaf */
			return (node); /* Need to fix double black */
	}
	else
	{ /* Node has one child */
		if (node->color == BLACK)
			child->color = BLACK; /* Hdle where node is blk & has a child */

		transplant(node, child);
	}
	free(node); /* Free node after fixing tree */
	return (child); /* Return new root */
}

/**
* transplant - Replaces one subtree with another.
* @u: PTR to the node to be replaced.
* @v: PTR to the node to replace it with.
*
* Updates the parent PTRs accordingly.
*/
void transplant(rb_tree_t *u, rb_tree_t *v)
{
	if (!u->parent)
	{
		/* If u is root, set root to v */
		u->parent = v->parent;
	}
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}

	if (v)
		v->parent = u->parent;
}

/**
* fix_remove - Fixes the red-black tree after a node has been removed.
* @root: PTR to the root of the tree.
* @node: PTR to the node that may need fixing.
*
* Return: PTR to the new root of the tree after fixing.
*/
rb_tree_t *fix_remove(rb_tree_t *root, rb_tree_t *node)
{
	while (node != root && node->color == BLACK)
	{
		if (node == node->parent->left)
		{
			root = process_left_child_case(root, node);
		}
		else
		{
			root = process_right_child_case(root, node);
		}
	}

	node->color = BLACK; /* Ensure root is always black */
	return (root);
}
