#include <stdlib.h>
#include <string.h>
#include "nary_trees.h"

/**
* nary_tree_insert - Inserts a node into a N-ary tree
* @parent: Pointer to parent node
* @str: String to be stored in created node
*
* Return: Pointer to newly created node, or NULL on failure
*/
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *new_node;

	/* Allocate memory for new node */
	new_node = malloc(sizeof(nary_tree_t));
	if (!new_node)
		return (NULL);
	/* Duplicate string and assign it to content */
	new_node->content = strdup(str);
	if (!new_node->content)
	{
		free(new_node);  /* Free node if strdup fails */
		return (NULL);
	}
	/* Initialize node */
	new_node->parent = parent;
	new_node->nb_children = 0;
	new_node->children = NULL;
	new_node->next = NULL;
	/* If parent is not NULL, insert node at beginning of children's list */
	if (parent)
	{
		new_node->next = parent->children;
		parent->children = new_node;
		parent->nb_children++;
	}
	return (new_node);
}