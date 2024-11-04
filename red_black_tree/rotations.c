#include "rb_trees.h"

/**
* right_rotate - Performs a right rotation on a node in the red-black tree.
* @root: Double PTR to the root of the tree.
* @y: PTR to the node to be rotated.
*
* Return: PTR to the new root of the subtree after rotation.
*/
rb_tree_t *right_rotate(rb_tree_t **root, rb_tree_t *y)
{
	rb_tree_t *x = y->left;

	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == NULL)
	{
		*root = x;
	}
	else if (y == y->parent->right)
	{
		y->parent->right = x;
	}
	else
	{
		y->parent->left = x;
	}

	x->right = y;
	y->parent = x;

	return *root;
}

/**
* left_rotate - Performs a left rotation on a node in the red-black tree.
* @root: Double PTR to the root of the tree.
* @x: PTR to the node to be rotated.
*
* Return: PTR to the new root of the subtree after rotation.
*/
rb_tree_t *left_rotate(rb_tree_t **root, rb_tree_t *x)
{
	rb_tree_t *y = x->right;

	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == NULL)
	{
		*root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;

	return *root;
}
