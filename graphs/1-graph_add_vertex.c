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
    vertex_t *current;

    /* Check if the graph or string is NULL */
    if (!graph || !str)
        return NULL;

    /* Allocate memory for the new vertex */
    new_vertex = malloc(sizeof(vertex_t));
    if (!new_vertex)
        return NULL;

    /* Duplicate the string content for the new vertex */
    new_vertex->content = strdup(str); 
    if (!new_vertex->content) {
        free(new_vertex);
        return NULL;
    }

    /* Set the new vertex properties */
    new_vertex->index = graph->nb_vertices++;
    new_vertex->nb_edges = 0;
    new_vertex->edges = NULL;
    new_vertex->next = NULL;

    /* If the graph has no vertices, this will be the first one */
    if (graph->vertices == NULL) {
        graph->vertices = new_vertex;
    } else {
        /* Traverse to the last vertex and add the new one at the end */
        current = graph->vertices;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_vertex;
    }

    return new_vertex;
}
