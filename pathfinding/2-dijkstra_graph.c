#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>


/*  Dijkstra's algorithm to find shortest path in a graph */
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
	/* Create a priority */
		return (NULL);

	/* Set all distances to infinity and previous vertices to NULL */
	for (size_t i = 0; i < num_vertices; i++)
	{
		distances[i] = INT_MAX;
		previous[i] = NULL;
		visited[i] = false;
	}

	/* Find index of start and target vertices */
	size_t start_index = start->index;
	size_t target_index = target->index;

	/* Set distance of start vertex to 0 */
	distances[start_index] = 0;

	/* Create a priority queue of vertices ordered by their current distance */
	/* For simplicity, let's assume priority queue is a simple sorted array. */
	vertex_t **queue = (vertex_t **)malloc(num_vertices * sizeof(vertex_t *));
	size_t queue_size = 0;

	queue[queue_size++] = (vertex_t *)start; /* Add start vertex to queue */

	while (queue_size > 0)
	{
		/* Extract vertex with minimum distance */
		vertex_t *current = queue[0]; /* first element has minimum distance */

		queue_size--;

		/* If we have already visited this vertex, continue */
		if (visited[current->index])
			continue;

		/* Mark vertex as visited */
		visited[current->index] = true;

		/* If we have reached target vertex, stop processing */
		if (current->index == target_index)
			break;

		/* Process each of neighbors of current vertex */
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
				queue[queue_size++] = neighbor;
			}
			edge = edge->next;
		}
	}

	/* If target vertex is unreachable, return NULL */
	if (distances[target_index] == INT_MAX)
	{
		free(distances);
		free(previous);
		free(visited);
		return (NULL);
	}

	/* Reconstruct path from target vertex to start vertex */
	const vertex_t *current = target;

	while (current != NULL)
	{
		queue_push_front(path, current->content);
		current = previous[current->index];
	}

	/* Clean up */
	free(distances);
	free(previous);
	free(visited);
	return (path);
}
