/**
* process_left_child_case - Handles the case when the node is a left child.
* @root: PTR to the root of the tree.
* @node: PTR to the node that may need fixing.
*
* Returns: PTR to the new root of the tree after fixing.
*/
rb_tree_t *process_left_child_case(rb_tree_t *root, rb_tree_t *node)
{
	rb_tree_t *sibling = node->parent->right;

	if (sibling->color == RED)
	{ /* Case 1: Sibling is red */
		sibling->color = BLACK;
		node->parent->color = RED;
		root = left_rotate(root, node->parent); /* Perform left rotation */
		sibling = node->parent->right; /* Update sibling */
	}
	if ((sibling->left == NULL || sibling->left->color == BLACK) &&
		(sibling->right == NULL || sibling->right->color == BLACK))
	{
		sibling->color = RED; /* Case 2: Both of sibling's children are black */
		node = node->parent; /* Move up to parent */
	}
	else
	{
		if (sibling->right == NULL || sibling->right->color == BLACK)
		{
			if (sibling->left) /* Case 3: Sibling's left child is red */
				sibling->left->color = BLACK;
			sibling->color = RED;
			root = right_rotate(root, sibling); /* Perform right rotation */
			sibling = node->parent->right; /* Update sibling */
		}
		sibling->color = node->parent->color; /* Case 4: sib's rt chld is red */
		node->parent->color = BLACK;
		if (sibling->right)
			sibling->right->color = BLACK;
		root = left_rotate(root, node->parent); /* Perform left rotation */
		node = root; /* Move to root */
	}

	return (root);
}

/**
* process_right_child_case - Handles the case when the node is a right child.
* @root: PTR to the root of the tree.
* @node: PTR to the node that may need fixing.
*
* Returns: PTR to the new root of the tree after fixing.
*/
rb_tree_t *process_right_child_case(rb_tree_t *root, rb_tree_t *node)
{
	rb_tree_t *sibling = node->parent->left;

	if (sibling->color == RED)
	{ /* Case 1: Sibling is red */
		sibling->color = BLACK;
		node->parent->color = RED; /* Perform right rotation */
		root = right_rotate(root, node->parent);
		sibling = node->parent->left; /* Update sibling */
	}
	if ((sibling->right == NULL || sibling->right->color == BLACK) &&
		(sibling->left == NULL || sibling->left->color == BLACK))
	{ /* Case 2: Both of sibling's children are black */
		sibling->color = RED;
		node = node->parent; /* Move up to parent */
	}
	else
	{
		if (sibling->left == NULL || sibling->left->color == BLACK)
		{ /* Case 3: Sibling's right child is red */
			if (sibling->right)
				sibling->right->color = BLACK;
			sibling->color = RED;
			root = left_rotate(root, sibling); /* Perform left rotation */
			sibling = node->parent->left; /* Update sibling */
		}
		sibling->color = node->parent->color; /* Case 4 sib's lft chld is red */
		node->parent->color = BLACK;
		if (sibling->left)
			sibling->left->color = BLACK;
		root = right_rotate(root, node->parent); /* Perform right rotation */
		node = root; /* Move to root */
	}

	return (root);
}