#include "graphs.h"

/**
* graph_add_edge - Adds an edge between two vertices in the graph.
* @graph: PTR to the graph structure.
* @src: String representing the source vertex.
* @dest: String representing the destination vertex.
* @type: The type of the edge (unidirectional or bidirectional).
*
* Return: 1 on success (edge added), 0 on failure (e.g., if vertices not found or memory allocation fails).
*/

int graph_add_edge(graph_t *graph, const char *src, const char *dest, edge_type_t type) {
    vertex_t *src_vertex = find_vertex(graph, src);
    vertex_t *dest_vertex = find_vertex(graph, dest);

    if (!src_vertex || !dest_vertex)
        return 0;

    edge_t *new_edge = malloc(sizeof(edge_t));
    if (!new_edge)
        return 0;

    new_edge->dest = dest_vertex;
    new_edge->next = src_vertex->edges;
    src_vertex->edges = new_edge;

    if (type == BIDIRECTIONAL) {
        new_edge = malloc(sizeof(edge_t));
        if (!new_edge)
            return 0;
        new_edge->dest = src_vertex;
        new_edge->next = dest_vertex->edges;
        dest_vertex->edges = new_edge;
    }

    return 1;
}