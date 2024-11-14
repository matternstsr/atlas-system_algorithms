#include "graphs.h"
#include "queue.h"
#include "queue.c"

/**
* breadth_first_traverse - Performs a breadth-first traversal of the graph.
* @graph: PTR to the graph structure.
* @action: Callback function to be called for each vertex during the traversal.
*          It receives the vertex and its depth.
*
* Return: The maximum depth reached during the traversal.
*/

size_t breadth_first_traverse(
	const graph_t *graph,
	void (*action)(const vertex_t *v, size_t depth)
)
{
	if (!graph || !action)
		return (0);

	size_t max_depth = 0;
	bool *visited = calloc(graph->nb_vertices, sizeof(bool));

	if (!visited)
		return (0);

	queue_t *queue = queue_create(graph->nb_vertices); /* Create the queue */

	if (!queue)
	{
		free(visited);
		return (0);
	}

	queue_enqueue(queue, graph->vertices); /* Enqueue the first vertex */
	visited[graph->vertices->index] = true;

	max_depth = bfs_process_queue(queue, visited, action, graph->nb_vertices);

	free(visited);
	queue_delete(queue);
	return (max_depth);
}


/**
* bfs_process_queue - Processes vertices in the queue during BFS.
* @queue: The queue holding the vertices to be processed.
* @visited: Boolean array to track visited vertices.
* @action: Callback function to be called for each vertex.
* @max_vertices: The total number of vertices in the graph.
*
* Return: The maximum depth reached during traversal.
*/

size_t bfs_process_queue(
	queue_t *queue,
	bool *visited,
	void (*action)(const vertex_t *v, size_t depth),
	size_t max_vertices
)
{
	size_t max_depth = 0;
	size_t depth = 0;

	while (!queue_is_empty(queue))
	{
		size_t queue_size = queue->size;  /* # of vertices at current level */
		/* Process vertices at current level */
		for (size_t i = 0; i < queue_size; i++)
		{
			vertex_t *vertex = queue_dequeue(queue);

			action(vertex, depth);

			edge_t *edge = vertex->edges;

			while (edge)
			{
				if (!visited[edge->dest->index])
				{
					visited[edge->dest->index] = true;
					queue_enqueue(queue, edge->dest);
				}
				edge = edge->next;
			}
		}
		depth++; /* Increment depth after processing current level */
		if (depth > max_depth) /* Update max depth if necessary */
			max_depth = depth;
	}

	return (max_depth);
}
