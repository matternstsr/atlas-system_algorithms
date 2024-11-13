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
    new_edge->next = NULL;

    /* Insert at the end of the list (preserving order) */
    if (!src_vertex->edges) {
        src_vertex->edges = new_edge;  /* First edge */
    } else {
        edge_t *current = src_vertex->edges;
        while (current->next) {
            current = current->next;  /* Find the last edge */
        }
        current->next = new_edge;  /* Add new edge to the end */
    }

    if (type == BIDIRECTIONAL) {
        new_edge = malloc(sizeof(edge_t));
        if (!new_edge)
            return 0;

        new_edge->dest = src_vertex;
        new_edge->next = NULL;

        /* Insert at the end of the list for the destination vertex as well */
        if (!dest_vertex->edges) {
            dest_vertex->edges = new_edge;  /* First edge for destination vertex */
        } else {
            edge_t *current = dest_vertex->edges;
            while (current->next) {
                current = current->next;  /* Find the last edge */
            }
            current->next = new_edge;  /* Add new edge to the end */
        }
    }

    return 1;
}


/**
 * find_vertex - Finds a vertex by its string content in the graph.
 * @graph: The graph where the vertex should be searched.
 * @str: The string content of the vertex to find.
 *
 * Return: A pointer to the vertex if found, or NULL if not found.
 */
vertex_t *find_vertex(const graph_t *graph, const char *str) {
    vertex_t *current = graph->vertices;

    while (current) {
        if (strcmp(current->content, str) == 0) {
            return current;  /* Vertex found */
        }
        current = current->next;

    }
    return NULL;  /* Vertex not found */
}