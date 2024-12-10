#include "nary_trees.h"
#include <stdio.h>

/**
* helper_diameter - A helper function to calculate the height and diameter
* @root: The current node
* @diameter: The current maximum diameter encountered
* Return: The height of the current node
*/
size_t helper_diameter(nary_tree_t const *root, size_t *diameter)
{
    if (!root)
        return (0);

    size_t max_height1 = 0, max_height2 = 0;
    nary_tree_t const *child = root->children;

    printf("Visiting node: %s\n", root->content);

    /* Traverse the children and calculate their heights */
    while (child)
    {
        size_t child_height = helper_diameter(child, diameter);

        printf("Child height for %s: %zu\n", child->content, child_height);

        /* Update the two largest heights */
        if (child_height > max_height1)
        {
            max_height2 = max_height1;
            max_height1 = child_height;
        }
        else if (child_height > max_height2)
        {
            max_height2 = child_height;
        }
        child = child->next;
    }

    /* Update the diameter with the sum of the two largest heights */
    if (max_height1 + max_height2 > *diameter)
    {
        printf("Updated diameter: %zu\n", max_height1 + max_height2);
        *diameter = max_height1 + max_height2;
    }

    /* Return the height of the current node */
    return (max_height1 + 1);
}

/**
* nary_tree_diameter - Computes the diameter of the N-ary tree
* @root: The root of the N-ary tree
* Return: The diameter of the tree
*/
size_t nary_tree_diameter(nary_tree_t const *root)
{
    size_t diameter = 0;

    /* Call the helper function to calculate the height and diameter */
    helper_diameter(root, &diameter);
    return (diameter);
}
