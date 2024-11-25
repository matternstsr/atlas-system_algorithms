#include <stdlib.h>
#include "heap.h"

/**
 * heap_extract - Extracts the root value from the Min Binary Heap
 * @heap: Pointer to the heap to extract the value from
 *
 * Return: Pointer to the extracted value, or NULL if it fails
 */
void *heap_extract(heap_t *heap)
{
    void *data;

    if (!heap || !heap->root)
        return (NULL);

    data = heap->root->data;

    /* Replace root with the last element (bottom-right most leaf) */
    if (heap->size > 1)
    {
        /* Move the last node to the root */
        heap->root->data = heap->root->children[heap->size - 1]->data;
        
        /* Fix the heap property */
        heapify(heap, heap->root);
    }

    /* Decrease heap size */
    heap->size--;

    return (data);
}

/**
 * heapify - Restore the heap property by rearranging nodes.
 * @heap: The heap in which the property is to be fixed.
 * @node: The node to be heapified.
 */
void heapify(heap_t *heap, heap_node_t *node)
{
    int smallest = node;
    int left = 2 * node + 1;
    int right = 2 * node + 2;

    if (left < heap->size && heap->nodes[left] < heap->nodes[smallest])
        smallest = left;

    if (right < heap->size && heap->nodes[right] < heap->nodes[smallest])
        smallest = right;

    if (smallest != node)
    {
        swap(&heap->nodes[node], &heap->nodes[smallest]);
        heapify(heap, heap->nodes[smallest]);
    }
}
