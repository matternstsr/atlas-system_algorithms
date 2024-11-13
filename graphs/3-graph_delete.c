#include "graphs.h"

/**
* graph_delete - Del all vertices & edges in graph & frees associated memory.
* @graph: PTR to the graph structure to be deleted.
*
* Return: void (No return value).
*/

void graph_delete(graph_t *graph)
{
	if (!graph)
		return;

	vertex_t *vertex = graph->vertices;

	while (vertex)
	{
		edge_t *edge = vertex->edges;

		while (edge)
		{
			edge_t *temp = edge;

			edge = edge->next;

			free(temp);
		}
		free(vertex->content);
		vertex_t *temp = vertex;

		vertex = vertex->next;

		free(temp);
	}

	free(graph);
}
