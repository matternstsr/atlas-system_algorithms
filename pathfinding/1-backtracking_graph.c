#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
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
	(void)graph;
	(void)start;
	(void)target;
	queue_t *queue = create_queue();  /* Initialize queue to store the path */

	/* Start the recursive backtracking process */
	if (!backtrack(graph, start, target, queue))
	{
		/* If no path is found, clean up */
		free(queue);
		return (NULL);
	}
	return (queue);  /* Return the queue containing the path */
}

/* Function to create and initialize a graph */
graph_t *graph_create(void) {
    graph_t *graph = malloc(sizeof(graph_t));
    if (!graph) {
        return NULL;  /* Return NULL if memory allocation fails */
    }
    graph->vertices = NULL;  /* Initialize the vertex array (optional, here as NULL) */
    graph->num_vertices = 0; /* Initially, there are no vertices */
    return graph;
}

/* Function to add a vertex to the graph */
vertex_t *graph_add_vertex(graph_t *graph, const char *name, int x, int y) {
    /* Allocate memory for the new vertex */
    vertex_t *vertex = malloc(sizeof(vertex_t));
    if (!vertex) {
        return NULL;  /* Return NULL if memory allocation fails */
    }

    /* Assign values to the vertex */
    vertex->name = strdup(name);  /* Duplicate the name string */
    vertex->x = x;
    vertex->y = y;

    /* Expand the vertices array to hold the new vertex */
    graph->vertices = realloc(graph->vertices, sizeof(vertex_t*) * (graph->num_vertices + 1));
    if (!graph->vertices) {
        free(vertex);  /* Free the allocated vertex if realloc fails */
        return NULL;
    }

    /* Add the vertex to the array and update the count */
    graph->vertices[graph->num_vertices] = vertex;
    graph->num_vertices++;

    return vertex;
}

/* Function to add an edge between two vertices in the graph */
void graph_add_edge(graph_t *graph, const char *start, const char *end, int weight, int bidirectional) {
    /* Find the start and end vertices by name */
    vertex_t *start_vertex = find_vertex_by_name(graph, start);
    vertex_t *end_vertex = find_vertex_by_name(graph, end);

    if (!start_vertex || !end_vertex) {
        return;  /* If either vertex is not found, return early */
    }

    /* Handle adding the edge (details depend on the graph structure, e.g., adjacency list) */
    printf("Adding edge between %s and %s with weight %d\n", start, end, weight);
    /* If bidirectional, add both directions (this is a simplified example) */
    if (bidirectional) {
        /* Add reverse edge as well (this would involve modifying adjacency lists, etc.) */
        printf("Adding bidirectional edge\n");
    }
}

/* Helper function to find a vertex by its name */
vertex_t *find_vertex_by_name(graph_t *graph, const char *name) {
    for (int i = 0; i < graph->num_vertices; i++) {
        if (strcmp(graph->vertices[i]->name, name) == 0) {
            return graph->vertices[i];
        }
    }
    return NULL;  /* Return NULL if vertex not found */
}

/* Function to delete the graph and free its memory */
void graph_delete(graph_t *graph) {
    if (!graph) {
        return;  /* Do nothing if graph is NULL */
    }

    /* Free all the vertices in the graph */
    for (int i = 0; i < graph->num_vertices; i++) {
        free(graph->vertices[i]->name);  /* Free the name of each vertex */
        free(graph->vertices[i]);        /* Free the vertex itself */
    }

    /* Free the vertices array */
    free(graph->vertices);

    /* Free the graph itself */
    free(graph);
}
