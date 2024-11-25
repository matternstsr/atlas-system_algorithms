#include <stdlib.h>
#include "huffman.h"

/**
 * symbol_create - Creates a new symbol structure.
 * @data: The character to store in the symbol structure.
 * @freq: The frequency associated with the character.
 * Return: A pointer to the newly created symbol structure, or NULL if
 *         memory allocation fails.
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbol = malloc(sizeof(symbol_t));

	if (!symbol)
		return (NULL);

	symbol->data = data;
	symbol->freq = freq;

	return (symbol);
}
