#include "graphs.h"

/**
* depth_first_traverse - Performs a depth-first traversal of the graph.
* @graph: PTR to the graph structure.
* @action: called for each vertex during traversal. It rec vertex & its depth.
*
* Return: The maximum depth reached during the traversal.
*/

static void dfs(
	vertex_t *vertex,
	size_t depth,
	bool *visited,
	size_t *max_depth,
	void (*action)(const vertex_t *v, size_t depth)
);
{
	visited[vertex->index] = true;

	action(vertex, depth);

	if (depth > *max_depth)
		*max_depth = depth;

	edge_t *edge = vertex->edges;

	while (edge)
	{
		if (!visited[edge->dest->index])
			dfs(edge->dest, depth + 1, visited, max_depth, action);
		edge = edge->next;
	}
}

size_t depth_first_traverse(
	const graph_t *graph,
	void (*action)(const vertex_t *v, size_t depth)
);
{
	if (!graph || !action)
		return (0);

	size_t max_depth = 0;
	bool *visited = calloc(graph->nb_vertices, sizeof(bool));

	if (!visited)
		return (0);

	if (graph->vertices)
		dfs(graph->vertices, 0, visited, &max_depth, action);

	free(visited);
	return (max_depth);
}
