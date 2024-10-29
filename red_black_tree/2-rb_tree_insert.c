#include "rb_trees.h"

/* 
* rb_tree_insert - Inserts a new value into the red-black tree.
* @tree: Double pointer to the root of the red-black tree.
* @value: Value to be inserted into the tree.
*
* Return: Pointer to the newly inserted node, or NULL if allocation fails.
*/
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	/* Create a new red-black tree node with the given value */
	rb_tree_t *new_node = rb_tree_node(NULL, value, RED);
	if (!new_node) /* Check if the new node was created successfully */
		return NULL; /* Return NULL if allocation fails */

	/* If the tree is empty, make the new node the root */
	if (!*tree)
	{
		new_node->color = BLACK; /* Set the root node's color to black */
		*tree = new_node; /* Set the tree to the new node */
		return new_node; /* Return the new node */
	}
	/* Insert the new node into the appropriate position in the tree */
	bst_insert(tree, new_node);
	/* Fix any violations of red-black tree properties after insertion */
	fix_insert(tree, new_node);
	return new_node; /* Return the newly inserted node */
}

static void fix_insert(rb_tree_t **tree, rb_tree_t *node)
{
	/* Initialize pointers for parent and grandparent nodes */
	rb_tree_t *parent = NULL;
	rb_tree_t *grandparent = NULL;

	/* Loop while the node is not the root and its parent is red */
	while ((node != *tree) && (node->color == RED) &&
			(node->parent->color == RED))
	{
		parent = node->parent; /* Get the parent of the current node */
		grandparent = parent->parent; /* Get grandparent of current node */

		if (parent == grandparent->left)
		{
			/* Case: Parent is the left child of the grandparent */
			rb_tree_t *uncle = grandparent->right; /* Get the uncle node */

			if (uncle && uncle->color == RED)
			{
				/* Case: Uncle is red */
				grandparent->color = RED; /* Recolor grandparent to red */
				parent->color = BLACK; /* Recolor parent to black */
				uncle->color = BLACK; /* Recolor uncle to black */
				node = grandparent; /* Move up the tree */
			}
			else
			{
				if (node == parent->right)
				{
					/* Case: Node is right child of its parent */
					/* Left rotation */
					parent->right = node->left; /* Move left child to parent */
					if (node->left)
						node->left->parent = parent; /* Update parent ptr */
					node->left = parent; /* Make parent left child of node */
					parent->parent = node; /* Update parent pointer */
					node = parent; /* Update node to the new parent */
				}
				parent->color = BLACK; /* Recolor parent to black */
				grandparent->color = RED; /* Recolor grandparent to red */
				/* Right rotation */
				grandparent->left = node->right; /* Move right child to gparent */
				if (node->right)
					node->right->parent = grandparent; /* Update parent pointer */
				node->right = grandparent; /* Make gparent right child of node */
			}
		}
		else
		{
			/* Case: Parent is right child of the gparent */
			rb_tree_t *uncle = grandparent->left; /* Get the uncle node */

			if (uncle && uncle->color == RED)
			{
				/* Case: Uncle is red */
				grandparent->color = RED; /* Recolor grandparent to red */
				parent->color = BLACK; /* Recolor parent to black */
				uncle->color = BLACK; /* Recolor uncle to black */
				node = grandparent; /* Move up the tree */
			}
			else
			{
				if (node == parent->left)
				{
					/* Case: Node is left child of its parent (right rotate ) */
					/* Right rotation */
					parent->left = node->right; /* Move right child to parent */
					if (node->right)
						node->right->parent = parent; /* Update parent prt */
					node->right = parent; /* Make parent right child of node */
					parent->parent = node; /* Update parent pointer */
					node = parent; /* Update node to the new parent */
				}
				parent->color = BLACK; /* Recolor parent to black */
				grandparent->color = RED; /* Recolor grandparent to red */
				/* Left rotation and Move node's left child to gparent */
				grandparent->right = node->left;
				if (node->left)
					node->left->parent = grandparent; /* Update parent ptr */
				node->left = grandparent; /* Make gparent left child of node */
			}
		}
	}

	(*tree)->color = BLACK; /* Ensure the root is always black */
}



static rb_tree_t *bst_insert(rb_tree_t **tree, rb_tree_t *new_node)
{
	/* Initialize pointers for the parent and the current node */
	rb_tree_t *parent = NULL;
	rb_tree_t *current = *tree;

	/* Traverse the tree to find the correct insertion point */
	while (current)
	{
		parent = current; /* Keep track of the parent */
		if (new_node->n < current->n)
			current = current->left; /* Move to the left child */
		else if (new_node->n > current->n)
			current = current->right; /* Move to the right child */
		else
		{
			free(new_node); /* Value already exists, free the new node */
			return NULL; /* Return NULL to indicate failure */
		}
	}

	new_node->parent = parent; /* Set the parent of the new node */
	if (!parent)
		*tree = new_node; /* Tree was empty, new node is now the root */
	else if (new_node->n < parent->n)
		parent->left = new_node; /* Insert as left child */
	else
		parent->right = new_node; /* Insert as right child */

	return new_node; /* Return the newly inserted node */
}
