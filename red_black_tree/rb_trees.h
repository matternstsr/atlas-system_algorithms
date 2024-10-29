#ifndef RB_TREES_H
#define RB_TREES_H

#include <stddef.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/**
* enum rb_color_e - Possible color of a Red-Black tree
*
* @RED: 0 -> Red node
* @BLACK: 1 -> Black node
*/
typedef enum rb_color_e
{
	RED = 0,
	BLACK,
	DOUBLE_BLACK
} rb_color_t;

/**
* struct rb_tree_s - Red-Black tree node structure
*
* @n: Integer stored in the node
* @parent: Pointer to the parent node
* @left: Pointer to the left child node
* @right: Pointer to the right child node
* @color: Color of the node (RED or BLACK)
*/
typedef struct rb_tree_s
{
	int n;
	rb_color_t color;
	struct rb_tree_s *parent;
	struct rb_tree_s *left;
	struct rb_tree_s *right;
} rb_tree_t;


/*functions */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color);
int rb_tree_is_valid(const rb_tree_t *tree);

/* Helper functions */
static int count_black_height(const rb_tree_t *tree);
static int check_colors(const rb_tree_t *tree);
static int check_bst(const rb_tree_t *tree, int min, int max);

#endif /* RB_TREES_H */
