#include "rb_trees.h"

/**
* rb_tree_is_valid - Checks if a red-black tree is valid.
* @tree: Pointer to the root of the red-black tree.
*
* Return: 1 if the tree is valid, 0 otherwise.
*/
int rb_tree_is_valid(const rb_tree_t *tree)
{
	/* Check if the tree is NULL */
	if (!tree)
		return (0); /* Return 0 for invalid tree */

	/* Check if the root node is black */
	if (tree->color != BLACK)
		return (0); /* Return 0 if root is not black */

	/* Check if the tree satisfies BST properties */
	if (!check_bst(tree, INT_MIN, INT_MAX))
		return (0); /* Return 0 if BST properties are violated */

	/* Check if colors are valid and count black height */
	return (check_colors(tree) && (count_black_height(tree) >= 0));
}

/**
* check_bst - Check if red-black tree satisfies binary search tree properties.
* @tree: Pointer to the root of the red-black tree.
* @min: Minimum allowable value for the current node.
* @max: Maximum allowable value for the current node.
*
* Return: 1 if the tree satisfies BST properties, 0 otherwise.
*/
int check_bst(const rb_tree_t *tree, int min, int max)
{
	/* If the current node is NULL, it's a valid subtree */
	if (!tree)
		return (1);

	/* Check if the current node's value is within the allowable range */
	if (tree->n < min || tree->n > max)
		return (0); /* Return 0 if the value is out of bounds */

	/* Recursively check the left and right subtrees */
	return (check_bst(tree->left, min, tree->n) &&
						check_bst(tree->right, tree->n, max));
}

/**
* check_colors - Validates the color properties of the red-black tree.
* @tree: Pointer to the root of the red-black tree.
*
* Return: 1 if color properties are valid, 0 otherwise.
*/
int check_colors(const rb_tree_t *tree)
{
	/* If the current node is NULL, it's a valid subtree */
	if (!tree)
		return (1);

	/* Check for violations of red node properties */
	if (tree->color == RED)
	{
		if ((tree->left && tree->left->color == RED) ||
			(tree->right && tree->right->color == RED))
			return (0); /* Return 0 if two consecutive red nodes are found */
	}

	/* Recursively check the left and right subtrees */
	return (check_colors(tree->left) && check_colors(tree->right));
}

/**
* count_black_height - Counts the black height of the red-black tree.
* @tree: Pointer to the root of the red-black tree.
*
* Return: The black height if valid, -1 if the tree is invalid.
*/
int count_black_height(const rb_tree_t *tree)
{
	/* If the current node is NULL, return 1 (counting as a black node) */
	if (!tree)
		return (1);

	/* Recursively count the black height of left and right subtrees */
	int left_height = count_black_height(tree->left);
	int right_height = count_black_height(tree->right);

	/* Check for invalid conditions: one subtree is invalid or heights differ */
	if (left_height == -1 || right_height == -1 || left_height != right_height)
		return (-1); /* Return -1 if the tree is invalid */

	/* Return the black height, increment if the current node is black */
	return (left_height + (tree->color == BLACK ? 1 : 0));
}
