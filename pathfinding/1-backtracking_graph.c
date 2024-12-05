#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


queue_t explore_vertex(vertex_t const *vert, vertex_t const *target,
					queue_t *path, int *visited);

/**
* backtracking_graph - Find a path start to target using recursive
*                      backtracking on a graph.
* @graph: The graph to explore.
* @start: The starting vertex.
* @target: The target vertex.
*
* Return: A queue that has path from start to target, NULL if no path found.
*/
queue_t *backtracking_graph(graph_t *graph,
							vertex_t const *start, vertex_t const *target)
{
	queue_t *path = NULL;
	path = calloc(1, sizeof(queue_t));

	if (!path)
		return (NULL);

	int *visited = calloc(graph->nb_vertices, sizeof(int));

	if (!visited)
	{
		free(path);
		return (NULL);
	}

	if (explore_vertex(start, target, path, visited))
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
* @vert: The vert vertex.
* @target: The target vertex.
* @path: The queue to store the path.
* @visited: Array to track visited vertices.
*
* Return: 1 if a path is found, otherwise 0.
*/
queue_t explore_vertex(vertex_t const *vert, vertex_t const *target,
					queue_t *path, int *visited)
{
	if (!vert || visited[vert->index])
		return (NULL);

	visited[vert->index] = 1;

	if (vert == target)
	{
		char *city_name = strdup(vert->content);

		queue_push_front(path, city_name);

		return (1);
	}
	queue_push_front(path, strdup(vert->content));

	for (size_t i = 0; i < graph->nb_vertices; i++)
	{
		if (graph_is_edge(graph, vert, &graph->vertices[i]))
		{
			if (explore_vertex(graph, &graph->vertices[i], target, path, visited))
				return (1);
		}
	}
	queue_push_front(path);
	return (0);
}
