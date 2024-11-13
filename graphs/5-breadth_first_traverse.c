#include "graphs.h"

/**
* breadth_first_traverse - Performs a breadth-first traversal of the graph.
* @graph: PTR to the graph structure.
* @action: Callback function to be called for each vertex during the traversal. It receives the vertex and its depth.
*
* Return: The maximum depth reached during the traversal.
*/

size_t breadth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth)) {
    if (!graph || !action)
        return 0;

    size_t max_depth = 0;
    bool *visited = calloc(graph->nb_vertices, sizeof(bool));
    if (!visited)
        return 0;

    queue_t *queue = queue_create();
    if (!queue) {
        free(visited);
        return 0;
    }

    queue_enqueue(queue, graph->vertices); /* Enqueue the first vertex */
    visited[graph->vertices->index] = true;

    size_t depth = 0;
    while (!queue_is_empty(queue)) {
        size_t queue_size = queue_size(queue);
        for (size_t i = 0; i < queue_size; i++) {
            vertex_t *vertex = queue_dequeue(queue);
            action(vertex, depth);

            edge_t *edge = vertex->edges;
            while (edge) {
                if (!visited[edge->dest->index]) {
                    visited[edge->dest->index] = true;
                    queue_enqueue(queue, edge->dest);
                }
                edge = edge->next;
            }
        }
        depth++;
    }

    free(visited);
    queue_delete(queue);
    return depth - 1; /* Return the max depth (last depth level) */
}
