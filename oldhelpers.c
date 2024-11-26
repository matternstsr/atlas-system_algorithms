#include "rb_trees.h"

static int check_bst(const rb_tree_t *tree, int min, int max)
{
	if (!tree)
		return 1;

	if (tree->n < min || tree->n > max)
		return 0;

	return check_bst(tree->left, min, tree->n) && check_bst(tree->right, tree->n, max);
}


static int check_colors(const rb_tree_t *tree)
{
	if (!tree)
		return 1;

	if (tree->color == RED)
	{
		if ((tree->left && tree->left->color == RED) ||
			(tree->right && tree->right->color == RED))
			return 0;
	}

	return check_colors(tree->left) && check_colors(tree->right);
}


static int count_black_height(const rb_tree_t *tree)
{
	if (!tree)
		return 1;

	int left_height = count_black_height(tree->left);
	int right_height = count_black_height(tree->right);

	if (left_height == -1 || right_height == -1 || left_height != right_height)
		return -1;

	return left_height + (tree->color == BLACK ? 1 : 0);
}


static void fix_insert(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *parent = NULL;
	rb_tree_t *grandparent = NULL;

	while ((node != *tree) && (node->color == RED) && (node->parent->color == RED))
	{
		parent = node->parent;
		grandparent = parent->parent;

		if (parent == grandparent->left)
		{
			rb_tree_t *uncle = grandparent->right;
			if (uncle && uncle->color == RED)
			{
				grandparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				node = grandparent;
			}
			else
			{
				if (node == parent->right)
				{
					/* Left rotation */
					/* (code for left rotation) */
				}
				parent->color = BLACK;
				grandparent->color = RED;
				/* Right rotation */
				/* (code for right rotation) */
				node = parent;
			}
		}
		else
		{
			/* Symmetric to the above */
		}
	}

	(*tree)->color = BLACK;
}


static rb_tree_t *bst_insert(rb_tree_t **tree, rb_tree_t *new_node)
{
	rb_tree_t *parent = NULL;
	rb_tree_t *current = *tree;

	while (current)
	{
		parent = current;
		if (new_node->n < current->n)
			current = current->left;
		else if (new_node->n > current->n)
			current = current->right;
		else
		{
			free(new_node);
			return NULL; /* Value already exists */
		}
	}

	new_node->parent = parent;
	if (!parent)
		*tree = new_node; /* Tree was empty */
	else if (new_node->n < parent->n)
		parent->left = new_node;
	else
		parent->right = new_node;

	return new_node;
}

static rb_tree_t *bst_remove(rb_tree_t *root, int n)
{
	rb_tree_t *node = root;
	rb_tree_t *temp = NULL;

	/* Find the node to be removed */
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
		return NULL; /* Node not found */

	/* Node has two children */
	if (node->left && node->right)
	{
		temp = node->right;
		while (temp->left)
			temp = temp->left;

		node->n = temp->n; /* Replace with successor value */
		node = temp; /* Now we will remove the successor */
	}

	/* Node has at most one child */
	rb_tree_t *child = (node->left) ? node->left : node->right;

	/* Remove node and handle the case of root */
	if (!child)
	{
		/* Node is a leaf */
		if (node->color == BLACK)
			return node; /* Need to fix double black */
	}
	else
	{
		/* Node has one child */
		if (node->color == BLACK)
			/* Handle case where node is black and has a child */
			child->color = BLACK;

		transplant(node, child);
	}

	/* Free the node after fixing the tree */
	free(node);
	return child; /* Return new root */
}

static void transplant(rb_tree_t *u, rb_tree_t *v)
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


static rb_tree_t *fix_remove(rb_tree_t *root, rb_tree_t *node)
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
				node = node->parent; /* Move up to the parent */
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
				node = root; /* Move to the root */
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
				node = node->parent; /* Move up to the parent */
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
				node = root; /* Move to the root */
			}
		}
	}

	node->color = BLACK; /* Ensure root is always black */
	return root;
}

static rb_tree_t *left_rotate(rb_tree_t *root, rb_tree_t *x)
{
	rb_tree_t *y = x->right;
	x->right = y->left;

	if (y->left != NULL)
		y->left->parent = x;

	y->parent = x->parent;

	if (x->parent == NULL)
	{
		root = y; /* y becomes the new root */
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

	return root;
}

static rb_tree_t *right_rotate(rb_tree_t *root, rb_tree_t *y)
{
	rb_tree_t *x = y->left;
	y->left = x->right;

	if (x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;

	if (y->parent == NULL)
	{
		root = x; /* x becomes the new root */
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

	return root;
}
