#include <stdlib.h>
#include "heap.h"

/**
* bubble_up - Bubbles a node up the heap to maintain heap property
* @node: The node to bubble up
* @heap: The heap structure containing the node
*/
void bubble_up(binary_tree_node_t *node, heap_t *heap)
{
    while (node->parent && heap->data_cmp(node->data, node->parent->data) < 0)
    {
        // Swap data between the node and its parent
        void *temp = node->data;
        node->data = node->parent->data;
        node->parent->data = temp;

        // Move up to the parent
        node = node->parent;
    }
}
