#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>


/*  Dijkstra's algorithm to find the shortest path in a graph */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
						vertex_t const *target)
{
	/* Initialize distances and previous pointers */
	size_t num_vertices = graph->nb_vertices;
	int *distances = (int *)malloc(num_vertices * sizeof(int));
	vertex_t **previous = (vertex_t **)malloc(num_vertices * sizeof(vertex_t *));
	bool *visited = (bool *)malloc(num_vertices * sizeof(bool));
	queue_t *path = queue_create();

	if (!distances || !previous || !visited || !path)
		return (NULL); /* Set all distances to infinity and previous vertices to NULL */
	for (size_t i = 0; i < num_vertices; i++)
	{
		distances[i] = INT_MAX;
		previous[i] = NULL;
		visited[i] = false;
	} /* Find index of start and target vertices */
	size_t start_index = start->index;
	size_t target_index = target->index;

	distances[start_index] = 0; /* Set distance of start vertex to 0 */

	/* Create a queue to hold vertices (sorted by distance) */
	vertex_t **queue = (vertex_t **)malloc(num_vertices * sizeof(vertex_t *));
	size_t queue_size = 0;

	queue[queue_size++] = (vertex_t *)start; /* Add start vertex to queue */

	while (queue_size > 0)
	{
		vertex_t *current = queue[0]; /* Extract vertex with minimum distance */

		/* Remove the first element (since it's the one with the minimum distance) */
		for (size_t i = 0; i < queue_size - 1; i++)
			queue[i] = queue[i + 1];
		queue_size--;

		if (visited[current->index]) /* If we have already visited this vertex, continue */
			continue;

		visited[current->index] = true; /* Mark vertex as visited */

		if (current->index == target_index) /* If we have reached target vertex, stop processing */
			break;

		/* Process each of the neighbors of the current vertex */
		edge_t *edge = current->edges;

		while (edge)
		{
			vertex_t *neighbor = edge->dest;
			int weight = edge->weight;

			/* Relax edge (update distance if a shorter path is found) */
			if (distances[current->index] + weight < distances[neighbor->index])
			{
				distances[neighbor->index] = distances[current->index] + weight;
				previous[neighbor->index] = current;
				queue[queue_size++] = neighbor; /* Add neighbor to the queue */
			}
			edge = edge->next;
		}
	}
	if (distances[target_index] == INT_MAX) /* If target vertex is unreachable, return NULL */
	{
		free(distances);
		free(previous);
		free(visited);
		free(queue);
		return (NULL);
	}
	const vertex_t *current = target; /* Reconstruct path from target vertex to start vertex */

	while (current != NULL)
	{
		queue_push_front(path, current->content);
		current = previous[current->index];
	}
	free(distances);  /* Clean up */
	free(previous);  /* Clean up */
	free(visited);  /* Clean up */
	free(queue);  /* Clean up */
	return (path);
}
