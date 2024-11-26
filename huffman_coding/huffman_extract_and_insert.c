#include <stdlib.h>
#include "huffman.h"


/**
* huffman_extract_and_insert - Extracts the two least frequent nodes from
* priority queue & inserts a new internal node with sum of their frequencies.
* @priority_queue: A ptr to the priority queue (min heap) from which the nodes
*                  will be extracted and into which new node will be inserted.
* Return: 1 on success, 0 on failure.
*/
int huffman_extract_and_insert(heap_t *priority_queue)
{
    if (heap_size(priority_queue) < 2)
        return (0);
    binary_tree_node_t *node1 = heap_extract(priority_queue);
    binary_tree_node_t *node2 = heap_extract(priority_queue);
    if (!node1 || !node2)
        return (0);
    symbol_t *new_symbol = symbol_create('\0', node1->data->freq + node2->data->freq);
    if (!new_symbol)
        return (0);
    binary_tree_node_t *new_node = binary_tree_node_create(new_symbol);
    if (!new_node)
        return (0);
    new_node->left = node1;
    new_node->right = node2;
    return (heap_insert(priority_queue, new_node));
}
