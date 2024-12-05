#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>

static int explore_vertex(graph_t *graph, vertex_t const *current,
							vertex_t const *target, queue_t *path,
							int *visited);

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
	queue_t *path = create_queue();

	if (!path)
		return (NULL);

	int *visited = calloc(graph->nb_vertices, sizeof(int));

	if (!visited)
	{
		free(path);
		return (NULL);
	}

	if (explore_vertex(graph, start, target, path, visited))
	{
		free(visited);
		return (path);
	}
	free(visited);
	free(path);
	return (NULL);
}

/**
* explore_vertex - Recursively explores neighboring vertices to find a path.
* @graph: The graph to explore.
* @current: The current vertex.
* @target: The target vertex.
* @path: The queue to store the path.
* @visited: Array to track visited vertices.
*
* Return: 1 if a path is found, otherwise 0.
*/
static int explore_vertex(graph_t *graph, vertex_t const *current,
							vertex_t const *target, queue_t *path, int *visited)
{
	if (!current || visited[current->index])
		return (0);

	visited[current->index] = 1;

	if (current == target)
	{
		char *city_name = strdup(current->content);

		enqueue(path, city_name);

		return (1);
	}

	enqueue(path, strdup(current->content));

	for (size_t i = 0; i < graph->nb_vertices; i++)
	{
		if (graph_is_edge(graph, current, &graph->vertices[i]))
		{
			if (explore_vertex(graph, &graph->vertices[i], target, path, visited))
				return (1);
		}
	}
	dequeue(path);
	return (0);
}
