#include "pathfinding.h"

/**
 * dijkstra_graph - Uses dijkstra method to find shortest path
 * @graph: Graph to find path in
 * @start: starting vertex
 * @target: Target Vertex
 * Return: Queue holding path or NULL
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
                        vertex_t const *target)
{
    queue_t *new_que = NULL;
    int *this_visit, *this_dist;
    vertex_t **prev, *vert = NULL;
    size_t i = 0;

    if (!graph || !start || !target)
        return (NULL);

    // Allocate memory for the queue and tracking arrays
    new_que = calloc(1, sizeof(queue_t));
    if (!new_que)
        return (NULL);

    this_visit = calloc(graph->nb_vertices, sizeof(int));
    if (!this_visit)
        return (free(new_que), NULL);

    this_dist = calloc(graph->nb_vertices, sizeof(int));
    if (!this_dist)
        return (free(this_visit), free(new_que), NULL);

    prev = calloc(graph->nb_vertices, sizeof(vertex_t *));
    if (!prev)
        return (free(this_dist), free(this_visit), free(new_que), NULL);

    // Initialize distances to infinity, except the start vertex
    for (i = 0; i < graph->nb_vertices; i++)
        this_dist[i] = INT_MAX;
    
    // Call find_dist to calculate shortest paths
    if (!find_dist(start, target, graph, this_visit, this_dist, prev))
    {
        free(prev), free(this_dist), free(this_visit), free(new_que);
        this_visit = NULL, this_dist = NULL, prev = NULL, new_que = NULL;
        return (NULL);
    }

    // Debug: print the distances to each vertex
    if (graph->vertices[i] != NULL)
    	printf("Checking %s, distance from %s is %d\n", graph->vertices[i]->content, start->content, this_dist[i]);

    // Reconstruct the path from target to start using prev array
    for (vert = prev[target->index]; prev[vert->index]; vert = prev[vert->index])
        queue_push_front(new_que, strdup(vert->content));

    // Push the start and target vertices into the queue
    queue_push_front(new_que, strdup(start->content));
    queue_push_back(new_que, strdup(target->content));

    // Free dynamically allocated memory
    free(prev), free(this_dist), free(this_visit);
    this_visit = NULL, this_dist = NULL, prev = NULL;

    return (new_que);
}

/**
 * find_dist - Calculates distance from Start
 * @start: starting node
 * @target: Target vertex
 * @graph: Graph to path
 * @this_visit: array to track if a node has been visited
 * @this_dist: array to track distance from Start
 * @prev: array of pointer to track path
 * Return: 1 on Success, 0 on fail.
 */
int find_dist(vertex_t const *start, vertex_t const *target, graph_t *graph,
              int *this_visit, int *this_dist, vertex_t **prev)
{
    int min_dist = INT_MAX;
    vertex_t *vert = NULL, *node = NULL;
    edge_t *this_edge = NULL;

    this_dist[start->index] = 0;

    // Main loop to calculate shortest path distances
    while (node != target)
    {
        min_dist = INT_MAX, node = NULL;

        // Find the unvisited vertex with the smallest distance
        for (vert = graph->vertices; vert; vert = vert->next)
        {
            if (!this_visit[vert->index] && this_dist[vert->index] < min_dist)
                min_dist = this_dist[vert->index], node = vert;
        }

        if (!node)
            break;

        this_visit[node->index] = 1;

        // Debug: print the current vertex being checked and its distance
        printf("Checking %s, distance from %s is %d\n", node->content,
               start->content, this_dist[node->index]);

        // Relax edges connected to the current vertex
        for (this_edge = node->edges; this_edge; this_edge = this_edge->next)
        {
            if (!this_visit[this_edge->dest->index] &&
                this_dist[this_edge->dest->index] >
                min_dist + this_edge->weight)
            {
                this_dist[this_edge->dest->index] = min_dist + this_edge->weight;
                prev[this_edge->dest->index] = node;
            }
        }
    }

    // If we haven't found the target, return failure
    if (!node || node != target)
        return (0);

    return (1);
}
