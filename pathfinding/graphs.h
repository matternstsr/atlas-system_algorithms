#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>

typedef struct vertex_s vertex_t;
typedef struct edge_s edge_t;
typedef struct graph_s graph_t;

/**
* graph_create - Creates a new empty graph.
* Return: A pointer to the new graph, or NULL if memory allocation fails.
*/
graph_t *graph_create(void);

/**
* graph_add_vertex - Adds a vertex to the graph.
* @graph: The graph to add the vertex to.
* @name: The name of the vertex to add.
* Return: A pointer to the newly added vertex, or NULL if failed.
*/
vertex_t *graph_add_vertex(graph_t *graph, const char *name);

/**
* graph_add_edge - Adds an edge between two vertices in the graph.
* @graph: The graph to add the edge to.
* @start: The starting vertex of the edge.
* @end: The ending vertex of the edge.
* @weight: The weight of the edge (e.g., distance or cost).
* @directional: Whether the edge is bidirectional or not.
* Return: 0 if the edge was added successfully, or -1 if failed.
*/
int graph_add_edge(graph_t *graph, vertex_t *start,
					vertex_t *end, int weight, int directional);

/**
* graph_delete - Deletes the entire graph and frees allocated memory.
* @graph: The graph to delete.
*/
void graph_delete(graph_t *graph);

/* Edge types (e.g., bidirectional) */
#define BIDIRECTIONAL 1
#define UNIDIRECTIONAL 0

/* Definition of the structures */

/**
* struct edge_s - Represents an edge in the graph.
* @vertex: The vertex that the edge points to.
* @weight: The weight of the edge (e.g., cost or distance).
*/
struct edge_s
{
	vertex_t *vertex;
	int weight;
};

/**
* struct vertex_s - Represents a vertex in the graph.
* @name: The name of the vertex.
* @edges: A list of edges connected to this vertex.
* @num_edges: The number of edges connected to the vertex.
*/
struct vertex_s
{
	char *name;
	edge_t *edges;
	size_t num_edges;
};

/**
* struct graph_s - Represents the entire graph.
* @vertices: A list of vertices in the graph.
* @num_vertices: The number of vertices in the graph.
*/
struct graph_s
{
	vertex_t **vertices;
	size_t num_vertices;
};

#endif /* GRAPH_H */
