#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stddef.h>
#include "binary_tree.h"
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
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size);
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);
int huffman_extract_and_insert(heap_t *priority_queue);
static void generate_huffman_codes(
	binary_tree_node_t *node,
	char *code, size_t depth);

#endif /* HUFFMAN_H */
