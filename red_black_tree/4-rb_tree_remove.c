#include "rb_trees.h"

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
	return (fix_remove)(root, node);
}

/**
 * bst_remove - Removes a node with a specified value from the red-black tree.
 * @root: Pointer to the root of the tree.
 * @n: Value of the node to be removed.
 *
 * Returns: Pointer to the new root of the tree, or NULL if the node was not found.
 */
rb_tree_t *bst_remove(rb_tree_t *root, int n)
{
	rb_tree_t *node = root;
	rb_tree_t *temp = NULL;

	/* Find node to be removed */
	while (node)
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

	/* Node has two children */
	if (node->left && node->right)
	{
		temp = node->right;
		while (temp->left)
			temp = temp->left;

		node->n = temp->n; /* Copy replacement's value to this node */
		node = temp; /* Prepare to remove the replacement */
	}

	/* Node has at most one child */
	rb_tree_t *child = (node->left) ? node->left : node->right;

	/* Remove node and handle case of root */
	if (!child)
	{
		/* Node is a leaf */
		if (node->color == BLACK)
			return (node); /* Need to fix double black */
	}
	else
	{
		/* Node has one child */
		if (node->color == BLACK)
			/* Handle case where node is black and has a child */
			child->color = BLACK;

		transplant(node, child);
	}

	/* Free node after fixing tree */
	free(node);
	return (child); /* Return new root */
}

/**
 * transplant - Replaces one subtree with another.
 * @u: Pointer to the node to be replaced.
 * @v: Pointer to the node to replace it with.
 *
 * Updates the parent pointers accordingly.
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
 * @root: Pointer to the root of the tree.
 * @node: Pointer to the node that may need fixing.
 *
 * Returns: Pointer to the new root of the tree after fixing.
 */
rb_tree_t *fix_remove(rb_tree_t *root, rb_tree_t *node)
{
	rb_tree_t *sibling;

	while (node != root && node->color == BLACK)
	{
		if (node == node->parent->left)
		{
			sibling = node->parent->right;

			if (sibling->color == RED)
			{
				/* Case 1: Sibling is red */
				sibling->color = BLACK;
				node->parent->color = RED;
				/* Perform left rotation */
				root = left_rotate(root, node->parent);
				sibling = node->parent->right; /* Update sibling */
			}

			if ((sibling->left == NULL || sibling->left->color == BLACK) &&
				(sibling->right == NULL || sibling->right->color == BLACK))
			{
				/* Case 2: Both of sibling's children are black */
				sibling->color = RED;
				node = node->parent; /* Move up to parent */
			}
			else
			{
				if (sibling->right == NULL || sibling->right->color == BLACK)
				{
					/* Case 3: Sibling's left child is red */
					if (sibling->left)
						sibling->left->color = BLACK;
					sibling->color = RED;
					/* Perform right rotation */
					root = right_rotate(root, sibling);
					sibling = node->parent->right; /* Update sibling */
				}

				/* Case 4: Sibling's right child is red */
				sibling->color = node->parent->color;
				node->parent->color = BLACK;
				if (sibling->right)
					sibling->right->color = BLACK;
				/* Perform left rotation */
				root = left_rotate(root, node->parent);
				node = root; /* Move to root */
			}
		}
		else
		{
			sibling = node->parent->left;

			if (sibling->color == RED)
			{
				/* Case 1: Sibling is red */
				sibling->color = BLACK;
				node->parent->color = RED;
				/* Perform right rotation */
				root = right_rotate(root, node->parent);
				sibling = node->parent->left; /* Update sibling */
			}

			if ((sibling->right == NULL || sibling->right->color == BLACK) &&
				(sibling->left == NULL || sibling->left->color == BLACK))
			{
				/* Case 2: Both of sibling's children are black */
				sibling->color = RED;
				node = node->parent; /* Move up to parent */
			}
			else
			{
				if (sibling->left == NULL || sibling->left->color == BLACK)
				{
					/* Case 3: Sibling's right child is red */
					if (sibling->right)
						sibling->right->color = BLACK;
					sibling->color = RED;
					/* Perform left rotation */
					root = left_rotate(root, sibling);
					sibling = node->parent->left; /* Update sibling */
				}

				/* Case 4: Sibling's left child is red */
				sibling->color = node->parent->color;
				node->parent->color = BLACK;
				if (sibling->left)
					sibling->left->color = BLACK;
				/* Perform right rotation */
				root = right_rotate(root, node->parent);
				node = root; /* Move to root */
			}
		}
	}

	node->color = BLACK; /* Ensure root is always black */
	return (root);
}

/**
 * left_rotate - Performs a left rotation on a node in the red-black tree.
 * @root: Pointer to the root of the tree.
 * @x: Pointer to the node to be rotated.
 *
 * Returns: Pointer to the new root of the tree after rotation.
 */
rb_tree_t *left_rotate(rb_tree_t *root, rb_tree_t *x)
{
	rb_tree_t *y = x->right;
	x->right = y->left;

	if (y->left != NULL)
		y->left->parent = x;

	y->parent = x->parent;

	if (x->parent == NULL)
	{
		root = y; /* y becomes new root */
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

	return (root);
}

/**
 * right_rotate - Performs a right rotation on a node in the red-black tree.
 * @root: Pointer to the root of the tree.
 * @y: Pointer to the node to be rotated.
 *
 * Returns: Pointer to the new root of the tree after rotation.
 */
rb_tree_t *right_rotate(rb_tree_t *root, rb_tree_t *y)
{
	rb_tree_t *x = y->left;
	y->left = x->right;

	if (x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;

	if (y->parent == NULL)
	{
		root = x; /* x becomes new root */
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

	return (root);
}
