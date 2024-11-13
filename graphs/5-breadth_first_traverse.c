#include "graphs.h"
#include "queue.h"
#include "queue.c"
#include "_names.h"

/**
* breadth_first_traverse - Performs a breadth-first traversal of the graph.
* @graph: PTR to the graph structure.
* @action: Callback function to be called for each vertex during the traversal.
*          It receives the vertex and its depth.
*
* Return: The maximum depth reached during the traversal.
*/

void breadth_first_traverse(graph_t *graph, void (*action)(Vertex)) {
    if (graph == NULL || graph->num_vertices == 0) {
        /* Handle empty graph or null graph case */
        return;
    }

    Queue *queue = create_queue();
    bool *visited = calloc(graph->num_vertices, sizeof(bool));

    for (int i = 0; i < graph->num_vertices; i++) {
        if (!visited[i]) {
            enqueue(queue, i);
            visited[i] = true;

            while (!is_empty(queue)) {
                int vertex = dequeue(queue);
                /* Perform the action if it's not NULL. */
                if (action != NULL) {
                    action(vertex);
                }

                /* Traverse all adjacent vertices. */
                for (int j = 0; j < graph->num_vertices; j++) {
                    if (graph->adjacency_matrix[vertex][j] && !visited[j]) {
                        enqueue(queue, j);
                        visited[j] = true;
                    }
                }
            }
        }
    }

    free(visited);
    free_queue(queue);
}
