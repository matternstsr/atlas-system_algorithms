#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>
#include "graphs.h"
/**
* backtracking_graph - Find a path start to target using recursive
*                      backtracking on a graph.
* @graph: The graph to explore.
* @start: The starting vertex.
* @target: The target vertex.
*
* Return: A queue that has path from start to target, NULL if no path found.
*/
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
								vertex_t const *target)
{
	queue_t *queue = create_queue();  /* Initialize queue to store path */

	return (queue);
}
