#include <stdlib.h>
#include "heap.h"

/**
* heap_delete - Deletes a heap
* @heap: Pointer to the heap to delete
* @free_data: Function to free the data stored in nodes
*/
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
    if (!heap)
        return;
    void delete_node(binary_tree_node_t *node)
    {
        if (!node)
            return;
        delete_node(node->left);
        delete_node(node->right);
        if (node->data)
            free_data(node->data);
        free(node);
    }
    delete_node(heap->root);
    free(heap);
}
