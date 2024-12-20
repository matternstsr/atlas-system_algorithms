#include "rb_trees.h"

/**
 * rb_tree_insert - Inserts a new value into red-black tree.
 * @tree: Double PTR to root of red-black tree.
 * @value: Value to be inserted into tree.
 *
 * Return: PTR to newly inserted node, or NULL if allocation fails.
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
    /* Create a new red-black tree node with given value */
    rb_tree_t *new_node = rb_tree_node(NULL, value, RED);
    if (!new_node) /* Check if new node was created successfully */
        return (NULL); /* Return NULL if allocation fails */

    /* If tree is empty, make new node root */
    if (!*tree)
    {
        new_node->color = BLACK; /* Set root node's color to black */
        *tree = new_node; /* Set tree to new node */
        return (new_node); /* Return new node */
    }

    /* Insert new node into appropriate position in tree */
    if (!bst_insert(tree, new_node))
    {
        free(new_node); /* Free new node if insertion failed */
        return (NULL); /* Return NULL to indicate failure */
    }

    /* Fix any violations of red-black tree properties after insertion */
    fix_insert(tree, new_node);
    return (new_node); /* Return newly inserted node */
}

/**
 * fix_insert - Fixes violations of red-black tree properties after insertion.
 * @tree: Double PTR to the root of the red-black tree.
 * @node: PTR to the newly inserted node.
 */
void fix_insert(rb_tree_t **tree, rb_tree_t *node)
{
    rb_tree_t *parent = NULL;
    rb_tree_t *grandparent = NULL;

    while ((node != *tree) && (node->color == RED) && 
           (node->parent && node->parent->color == RED))
    {
        parent = node->parent; /* Get parent of current node */
        grandparent = parent->parent; /* Get grandparent of current node */

        if (parent == grandparent->left)
        {
            rb_tree_t *uncle = grandparent->right; /* Get uncle node */

            if (uncle && uncle->color == RED)
            {
                /* Case: Uncle is red */
                grandparent->color = RED; /* Recolor grandparent to red */
                parent->color = BLACK; /* Recolor parent to black */
                uncle->color = BLACK; /* Recolor uncle to black */
                node = grandparent; /* Move up tree */
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
                    parent->parent = node; /* Update parent PTR */
                    node = parent; /* Update node to new parent */
                }
                parent->color = BLACK; /* Recolor parent to black */
                grandparent->color = RED; /* Recolor grandparent to red */
                /* Right rotation */
                grandparent->left = node->right; /* Move right child to gparent */
                if (node->right)
                    node->right->parent = grandparent; /* Update parent PTR */
                node->right = grandparent; /* Make gparent right child of node */
            }
        }
        else
        {
            /* Symmetric case for right child */
            rb_tree_t *uncle = grandparent->left; /* Get uncle node */
            if (uncle && uncle->color == RED)
            {
                /* Same logic as above */
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            }
            else
            {
                if (node == parent->left)
                {
                    /* Right rotation */
                    parent->left = node->right;
                    if (node->right)
                        node->right->parent = parent;
                    node->right = parent;
                    parent->parent = node;
                    node = parent;
                }
                parent->color = BLACK;
                grandparent->color = RED;
                grandparent->right = node->left;
                if (node->left)
                    node->left->parent = grandparent;
                node->left = grandparent;
            }
        }
    }

    (*tree)->color = BLACK; /* Ensure root is always black */
}

/**
 * bst_insert - Inserts a new node into the binary search tree.
 * @tree: Double PTR to the root of the tree.
 * @new_node: PTR to the new node to be inserted.
 *
 * Returns: PTR to the newly inserted node, or NULL if a duplicate value 
 * is found.
 */
rb_tree_t *bst_insert(rb_tree_t **tree, rb_tree_t *new_node)
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
            /* Duplicate value found */
            free(new_node); /* Free the new node */
            return (NULL); /* Return NULL to indicate failure */
        }
    }

    new_node->parent = parent;

    if (!parent)
    {
        *tree = new_node; /* Tree was empty; new node is now the root */
    }
    else if (new_node->n < parent->n)
    {
        parent->left = new_node; /* Insert as left child */
    }
    else
    {
        parent->right = new_node; /* Insert as right child */
    }

    return (new_node); /* Return newly inserted node */
}

