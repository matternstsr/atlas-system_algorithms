#ifndef GRAPHS_H
#define GRAPHS_H

#include <stddef.h>  /* For size_t */
#include <stdbool.h> /* For bool type */
#include <stdlib.h>  /* Malloc */
#include <string.h>  /* Strdup */
#include <stdio.h>   /* For I/O functions like printf, etc. */
#include <assert.h>  /* For debugging (optional) */

/**
 * enum edge_type_e - Enumerates the different types of
 * connection between two vertices.
 *
 * @UNIDIRECTIONAL: The connection is made only in one way
 * @BIDIRECTIONAL: The connection is made in two ways
 */
typedef enum edge_type_e
{
    UNIDIRECTIONAL = 0,
    BIDIRECTIONAL
} edge_type_t;

/* Forward declar of vertex_t for edge_t - resolve this circular dependency */
typedef struct vertex_s vertex_t;

/**
 * struct edge_s - Node in the linked list of edges for a given vertex
 * A single vertex can have many edges.
 *
 * @dest: Pointer to the connected vertex
 * @next: Pointer to the next edge
 */
typedef struct edge_s
{
    vertex_t    *dest;  /* Destination vertex */
    struct edge_s *next; /* Next edge in the list */
} edge_t;


/**
 * struct vertex_s - Node in the linked list of vertices in the adjacency list
 *
 * @index: Index of the vertex in the adjacency list
 * @content: Custom data stored in the vertex (a string)
 * @nb_edges: Number of connections with other vertices in the graph
 * @edges: Pointer to the head node of the linked list of edges
 * @next: Pointer to the next vertex in the adjacency list
 *   This pointer points to another vertex in the graph, but it doesn't
 *   represent an edge between the two vertices.
 */
struct vertex_s
{
    size_t      index;      /* Vertex index */
    char        *content;   /* String content for the vertex */
    size_t      nb_edges;   /* Number of outgoing edges */
    edge_t      *edges;     /* List of outgoing edges */
    struct vertex_s *next;  /* Next vertex in the adjacency list */
};

/**
 * struct graph_s - Representation of a graph
 * We use an adjacency linked list to represent our graph.
 *
 * @nb_vertices: Number of vertices in the graph
 * @vertices: Pointer to the head node of the adjacency list
 */
typedef struct graph_s
{
    size_t      nb_vertices;   /* Total number of vertices in the graph */
    vertex_t    *vertices;     /* Head of the adjacency list */
} graph_t;


/* Function prototypes */
graph_t *graph_create(void);
void graph_delete(graph_t *graph);
vertex_t *graph_add_vertex(graph_t *graph, const char *str);
int graph_add_edge(graph_t *graph, const char *src, const char *dest, edge_type_t type);
size_t depth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth));
size_t breadth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth));
void graph_display(const graph_t *graph);

#endif /* GRAPHS_H */
