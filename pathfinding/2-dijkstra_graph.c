#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
                       vertex_t const *target)
{
    int *dist, *visit;
    vertex_t **prev, *vert = NULL;
    size_t i = 0;
    queue_t *path = NULL;

    if (!graph || !start || !target)
        return (NULL);
    
    /* Allocate memory for path, visit array, and previous array */
    path = calloc(1, sizeof(queue_t));
    if (!path)
        return (NULL);
    visit = calloc(graph->nb_vertices, sizeof(int));
    if (!visit)
        return (NULL);
    prev = calloc(graph->nb_vertices, sizeof(vertex_t *));
    if (!prev)
        return (NULL);
    
    /* Initialize distances */
    dist = calloc(graph->nb_vertices, sizeof(int));
    if (!dist)
        return (NULL);
    for (i = 0; i < graph->nb_vertices; i++)
        dist[i] = INT_MAX;

    /* Run Dijkstra's algorithm to find the shortest path */
    if (find_dist(start, target, graph, visit, dist, prev))
    {
        free(prev), free(dist), free(visit), free(path);
        prev = NULL, dist = NULL, visit = NULL, path = NULL;
        return (NULL);
    }
    
    /* Debug: print the distance to each vertex */
    for (i = 0; i < graph->nb_vertices; i++) {
        printf("Checking %s, distance from %s is %d\n", graph->vertices[i]->content, start->content, dist[i]);
    }

    /* Reconstruct path from target to start using 'prev' array */
    for (vert = prev[target->index]; vert != NULL; vert = prev[vert->index])
        queue_push_front(path, strdup(vert->content));

    /* Add start vertex */
    queue_push_front(path, strdup(start->content)); 

    /* Clean up dynamically allocated memory */
    free(prev), free(dist), free(visit);
    prev = NULL, dist = NULL, visit = NULL;

    return (path);
}

bool find_dist(vertex_t const *start, vertex_t const *target, graph_t *graph,
               int *visit, int *dist, vertex_t **prev)
{
    size_t i, queue_size = 0, num_vertices = graph->nb_vertices;
    vertex_t **queue = malloc(num_vertices * sizeof(vertex_t *));
    if (!queue)
        return (true);

    initialize_dijkstra(start, graph, visit, dist, prev);
    queue[queue_size++] = (vertex_t *)start;

    while (queue_size > 0)
    {
        vertex_t *current = queue[0];

        for (i = 0; i < queue_size - 1; i++)
            queue[i] = queue[i + 1];
        queue_size--;

        if (process_vertex(current, target, visit))
            break;

        relax_edges(current->edges, current, dist, prev, queue, &queue_size);
    }

    free(queue);
    return (dist[target->index] == INT_MAX);
}

bool process_vertex(vertex_t *current, vertex_t const *target, int *visit)
{
    if (visit[current->index])
        return (false);
    visit[current->index] = 1;

    if (current == target)
        return (true);

    return (false);
}

void relax_edges(edge_t *edge, vertex_t *current, int *dist, vertex_t **prev,
                 vertex_t **queue, size_t *queue_size)
{
    while (edge)
    {
        vertex_t *neighbor = edge->dest;
        int weight = edge->weight;

        if (dist[current->index] + weight < dist[neighbor->index])
        {
            dist[neighbor->index] = dist[current->index] + weight;
            prev[neighbor->index] = current;
            queue[(*queue_size)++] = neighbor;
        }

        edge = edge->next;
    }
}

void initialize_dijkstra(vertex_t const *start, graph_t *graph, int *visit,
                         int *dist, vertex_t **prev)
{
    size_t i, num_vertices = graph->nb_vertices;

    for (i = 0; i < num_vertices; i++)
    {
        dist[i] = (i == start->index) ? 0 : INT_MAX;
        prev[i] = NULL;
        visit[i] = 0;
    }
}
