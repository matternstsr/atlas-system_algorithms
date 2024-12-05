#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
					vertex_t const *target)
{
	int *dist, *visit;
	vertex_t **prev, *vert = NULL;
	size_t i = 0;
	queue_t *path = NULL;

	if (!graph || !start || !target)
		return (NULL);
	/* Allocate memory for path, visit array, and previous array */
	path = calloc(1, sizeof(queue_t));
	if (!path)
		return (NULL);
	visit = calloc(graph->nb_vertices, sizeof(int));
	if (!visit)
		return (NULL);
	prev = calloc(graph->nb_vertices, sizeof(vertex_t *));
	if (!prev)
		return (NULL);
	/* Initialize distances */
	dist = calloc(graph->nb_vertices, sizeof(int));
	if (!dist)
		return (NULL);
	for (i = 0; i < graph->nb_vertices; i++)
		dist[i] = INT_MAX;
	/* Run Dijkstra's algorithm to find shortest path */
	if (find_dist(start, target, graph, visit, dist, prev))
	{
		free(prev), free(dist), free(visit), free(path);
		prev = NULL, dist = NULL, visit = NULL, path = NULL;
		return (NULL);
	}
	/* Reconstruct path from target to start using 'prev' array */
	for (vert = prev[target->index]; vert != NULL; vert = prev[vert->index])
		queue_push_front(path, strdup(vert->content));
	queue_push_front(path, strdup(start->content)); /* Add start vertex */
	queue_push_front(path, strdup(target->content)); /* Add target vertex */

	/* Clean up dynamically allocated memory */
	free(prev), free(dist), free(visit);
	prev = NULL, dist = NULL, visit = NULL;
	return (path);
}

bool find_dist(vertex_t const *start, vertex_t const *target, graph_t *graph,
			int *visit, int *dist, vertex_t **prev)
{
	size_t i;
	size_t num_vertices = graph->nb_vertices;

	/* Initialize distances */
	dist[start->index] = 0;  /* Start vertex distance is 0 */
	for (i = 0; i < num_vertices; i++)
	{
		if (i != start->index)
			dist[i] = INT_MAX;  /* All other distances are set to infinity */
		prev[i] = NULL;  /* Previous vertex is initially NULL for all */
		visit[i] = 0;     /* Mark all vertices as unvisited */
	}

	/* Create a priority queue to manage vertices (min-heap or sorted list) */
	/* Using a simple array as a queue for simplicity */
	vertex_t **queue = (vertex_t **)malloc(num_vertices * sizeof(vertex_t *));

	if (!queue)
		return (true); /* Return true on error (memory allocation failure) */

	size_t queue_size = 0;

	/* Add start vertex to queue */
	queue[queue_size++] = (vertex_t *)start;

	while (queue_size > 0)
	{
		/* Extract vertex with smallest distance */
		vertex_t *current = queue[0];

		/* Move first element to end of queue and reduce size */
		for (i = 0; i < queue_size - 1; i++)
			queue[i] = queue[i + 1];
		queue_size--;

		/* If we've already visited this vertex, skip it */
		if (visit[current->index])
			continue;

		visit[current->index] = 1;  /* Mark as visited */

		/* If we reach target vertex, we can stop early (optional optimization) */
		if (current == target)
			break;

		/* Process each of neighbors of current vertex */
		edge_t *edge = current->edges;

		while (edge)
		{
			vertex_t *neighbor = edge->dest;
			int weight = edge->weight;

			/* Relax edge (update distance if a shorter path is found) */
			if (dist[current->index] + weight < dist[neighbor->index])
			{
				dist[neighbor->index] = dist[current->index] + weight;
				prev[neighbor->index] = current;

				/* Add neighbor to queue (could optimize queue with a priority queue) */
				queue[queue_size++] = neighbor;
			}
			edge = edge->next;
		}
	}
	free(queue);  /* Clean up queue */
	/* If target vertex has not been visited, return true (indicating failure) */
	return (dist[target->index] == INT_MAX);
}
