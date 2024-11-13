#include "graphs.h"

/**
* graph_add_vertex - Adds a new vertex to the graph.
* @graph: PTR to the graph structure.
* @str: String to be stored as the content of the new vertex.
*
* Return: PTR to the newly added vertex, or NULL on failure (e.g., if memory allocation fails or vertex already exists).
*/

vertex_t *graph_add_vertex(graph_t *graph, const char *str) {
    vertex_t *new_vertex;
    if (!graph || !str)
        return NULL;

    new_vertex = malloc(sizeof(vertex_t));
    if (!new_vertex)
        return NULL;

    new_vertex->content = strdup(str); /* Allocate and copy the string */
    if (!new_vertex->content) {
        free(new_vertex);
        return NULL;
    }

    new_vertex->index = graph->nb_vertices++;
    new_vertex->nb_edges = 0;
    new_vertex->edges = NULL;
    new_vertex->next = graph->vertices;
    graph->vertices = new_vertex;
    return new_vertex;
}
