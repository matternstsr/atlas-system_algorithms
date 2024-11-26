#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"


/**
 * generate_huffman_codes - Recursively generates and prints the Huffman codes
 *                           for each symbol in the Huffman tree.
 * @node: A pointer to the current node in the Huffman tree.
 * @code: A string to hold the current Huffman code as the tree is traversed.
 * @depth: The current depth in the Huffman tree, representing the length of
 *         the current Huffman code.
 */
void generate_huffman_codes(
	binary_tree_node_t *node,
	char *code, size_t depth)
{
	if (!node)
		return;

	symbol_t *symbol = (symbol_t *)node->data;

	if (symbol && symbol->data != -1)
	{
		code[depth] = '\0';
		printf("%c: %s\n", symbol->data, code);
	}
	else
	{
		code[depth] = '0';
		generate_huffman_codes(node->left, code, depth + 1);
		code[depth] = '1';
		generate_huffman_codes(node->right, code, depth + 1);
	}
}


/**
 * huffman_codes - Builds Huffman tree from provided data and frequencies,
 *                 and generates the Huffman codes for each symbol.
 * @data: An array of characters representing the symbols.
 * @freq: An array of frequencies corresponding to each character in @data.
 * @size: The number of elements in @data and @freq arrays.
 * Return: 1 on success, 0 on failure.
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root = huffman_tree(data, freq, size);

	if (!root)
		return (0);

	char code[256];

	generate_huffman_codes(root, code, 0);

	return (1);
}
