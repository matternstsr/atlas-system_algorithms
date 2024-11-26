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

symbol_t *symbol_create(char data, size_t freq);
binary_tree_node_t *binary_tree_node_create(void *data);
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);
int huffman_extract_and_insert(heap_t *priority_queue);
void generate_huffman_codes(
	binary_tree_node_t *node,
	char *code, size_t depth);
void heap_destroy(heap_t *heap);
int symbol_compare(void *a, void *b);
void free_heap_nodes(binary_tree_node_t *node);
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size);
int huffman_codes(char *data, size_t *freq, size_t size);

#endif /* HUFFMAN_H */

