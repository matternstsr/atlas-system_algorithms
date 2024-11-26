#include "graphs.h"

/**
* graph_create - Initializes and allocates memory for a new graph.
* @void: No parameters.
*
* Return: PTR to a newly created graph structure, or NULL on failure.
*/

graph_t *graph_create(void)
{
	graph_t *graph = malloc(sizeof(graph_t));

	if (!graph)
		return (NULL);
	graph->nb_vertices = 0;

	graph->vertices = NULL;

	return (graph);
}
