#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heap.h"

/**
* struct symbol_s - Stores a char and its associated frequency
*
* @data: The character
* @freq: The associated frequency
*/
typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;

/* Function Prototypes */
heap_t *heap_create(int (*data_cmp)(void *, void *));
symbol_t *symbol_create(char character, size_t freq);
int heap_insert(heap_t *heap, binary_tree_node_t *node);
void heap_destroy(heap_t *heap);
void *heap_extract(heap_t *heap);
int symbol_compare(void *a, void *b);
binary_tree_node_t *binary_tree_node_create(void *data);
void heap_delete(heap_t *heap, void (*free_data)(void *));
void free_heap_nodes(binary_tree_node_t *node);

#endif /* HUFFMAN_H */

