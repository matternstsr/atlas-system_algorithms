#include "rb_trees.h"

/**
* rb_tree_node - Creates a new red-black tree node.
* @parent: Pointer to the parent node.
* @value: Value to be stored in the new node.
* @color: Color of the new node (red or black).
*
* Return: Pointer to the newly created node, or NULL if allocation fails.
*/
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	/* Allocate memory for a new rb_tree_t node and initialize to zero */
	rb_tree_t *node = calloc(1, sizeof(rb_tree_t));

	if (!node) /* Check if memory allocation was successful */
		return (NULL); /* Return NULL if allocation failed */

	/* Set the value of the new node */
	node->n = value;
	/* Set the color of the new node */
	node->color = color;
	/* Set the parent of the new node */
	node->parent = parent;

	/* Return the pointer to the newly created node */
	return (node);
}

/**
 * rb_tree_free - Frees all nodes in the red-black tree.
 * @node: Pointer to the root node of the tree.
 */
void rb_tree_free(rb_tree_t *node) {
    if (node) {
        rb_tree_free(node->left);
        rb_tree_free(node->right);
        free(node);
    }
}

void cleanup(rb_tree_t **root) {
    if (root && *root) {
        rb_tree_free(*root);
        *root = NULL; /* Avoid dangling pointer */
    }
}
