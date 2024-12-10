#include <stdlib.h>
#include "nary_trees.h"

/**
* nary_tree_traverse - Trav an N-ary tree and applies an action on each node.
* @root: Pointer to root of tree.
* @action: Func to execute for each node, it takes node and depth as arguments.
* Return: maximum depth of tree.
*/
size_t nary_tree_traverse(nary_tree_t const *root,
							void (*action)(nary_tree_t const *node,
							size_t depth))
{
    static size_t depth = 0;  /* Static var to track depth w/ recursive calls */

    if (!root || !action)
        return (0);
    /* Perform action on current node */
    action(root, depth);
    /* Traverse children */
    nary_tree_t const *child = root->children;
    while (child)
    {
        depth++;  /* Increase depth for child nodes */
        nary_tree_traverse(child, action);  /* Recursively traverse child */
        depth--;  /* Decrease depth when returning to parent */
        child = child->next;
    }
    return (depth);  /* Return maximum depth encountered */
}
