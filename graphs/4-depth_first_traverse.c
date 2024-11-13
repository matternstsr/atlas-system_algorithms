#include "graphs.h"

/**
* depth_first_traverse - Performs a depth-first traversal of the graph.
* @graph: PTR to the graph structure.
* @action: Callback function to be called for each vertex during the traversal. It receives the vertex and its depth.
*
* Return: The maximum depth reached during the traversal.
*/

size_t depth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth)) {
    if (!graph || !action)
        return 0;

    size_t max_depth = 0;
    bool *visited = calloc(graph->nb_vertices, sizeof(bool));
    if (!visited)
        return 0;

    void dfs(vertex_t *vertex, size_t depth) {
        visited[vertex->index] = true;
        action(vertex, depth);
        if (depth > max_depth)
            max_depth = depth;

        edge_t *edge = vertex->edges;
        while (edge) {
            if (!visited[edge->dest->index])
                dfs(edge->dest, depth + 1);
            edge = edge->next;
        }
    }

    if (graph->vertices)
        dfs(graph->vertices, 0);

    free(visited);
    return max_depth;
}
