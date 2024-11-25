#include <stdlib.h>
#include "heap.h"

/**
* binary_tree_node - Creates a new binary tree node
* @parent: Parent node of the node to be created
* @data: Data to be stored in the node
*
* Return: A pointer to the new node, or NULL if it fails
*/
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
    binary_tree_node_t *node;

    node = malloc(sizeof(binary_tree_node_t));
    if (!node)
        return (NULL);

    node->data = data;
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;

    return (node);
}
