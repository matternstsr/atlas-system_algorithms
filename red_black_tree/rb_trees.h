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
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value);
rb_tree_t *array_to_rb_tree(int *array, size_t size);
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n);



/* Helper functions */
int count_black_height(const rb_tree_t *tree);
int check_colors(const rb_tree_t *tree);
int check_bst(const rb_tree_t *tree, int min, int max);
void fix_insert(rb_tree_t **tree, rb_tree_t *node);
rb_tree_t *bst_insert(rb_tree_t **tree, rb_tree_t *new_node);
rb_tree_t *bst_remove(rb_tree_t *root, int n);
rb_tree_t *fix_remove(rb_tree_t *root, rb_tree_t *node);
void transplant(rb_tree_t *u, rb_tree_t *v);
rb_tree_t *right_rotate(rb_tree_t *root, rb_tree_t *y);
rb_tree_t *left_rotate(rb_tree_t *root, rb_tree_t *x);
void handle_right_child_case(rb_tree_t *node,
                              rb_tree_t *parent, rb_tree_t *grandparent);
void handle_left_child_case(rb_tree_t *node,
                             rb_tree_t *parent, rb_tree_t *grandparent);
rb_tree_t *process_right_child_case(rb_tree_t *root, rb_tree_t *node);
rb_tree_t *process_left_child_case(rb_tree_t *root, rb_tree_t *node);

#endif /* RB_TREES_H */
