#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/* A helper function to compare distances (used for priority queue sorting) */
static int compare_distances(const void *a, const void *b)
{
    return ((*(int *)a) - (*(int *)b));
}

/*  Dijkstra's algorithm to find the shortest path in a graph */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start, vertex_t const *target)
{
    /* Initialize the distances and previous pointers */
    size_t num_vertices = graph->nb_vertices;
    int *distances = (int *)malloc(num_vertices * sizeof(int));
    vertex_t **previous = (vertex_t **)malloc(num_vertices * sizeof(vertex_t *));
    bool *visited = (bool *)malloc(num_vertices * sizeof(bool));
    queue_t *path = queue_create();
    
    if (!distances || !previous || !visited || !path)
        return NULL;

    /* Set all distances to infinity and previous vertices to NULL */
    for (size_t i = 0; i < num_vertices; i++) {
        distances[i] = INT_MAX;
        previous[i] = NULL;
        visited[i] = false;
    }

    /* Find the index of the start and target vertices */
    size_t start_index = start->index;
    size_t target_index = target->index;

    /* Set the distance of the start vertex to 0 */
    distances[start_index] = 0;

    /* Create a priority queue of vertices ordered by their current distance */
    /* For simplicity, let's assume the priority queue is a simple sorted array. */
    vertex_t **queue = (vertex_t **)malloc(num_vertices * sizeof(vertex_t *));
    size_t queue_size = 0;
    queue[queue_size++] = (vertex_t *)start; /* Add the start vertex to the queue */

    while (queue_size > 0) {
        /* Extract the vertex with the minimum distance */
        vertex_t *current = queue[0]; /* The first element has the minimum distance */
        queue_size--;

        /* If we have already visited this vertex, continue */
        if (visited[current->index]) {
            continue;
        }

        /* Mark the vertex as visited */
        visited[current->index] = true;

        /* If we have reached the target vertex, stop processing */
        if (current->index == target_index) {
            break;
        }

        /* Process each of the neighbors of the current vertex */
        edge_t *edge = current->edges;
        while (edge) {
            vertex_t *neighbor = edge->dest;
            int weight = edge->weight;
            
            /* Relax the edge (update the distance if a shorter path is found) */
            if (distances[current->index] + weight < distances[neighbor->index]) {
                distances[neighbor->index] = distances[current->index] + weight;
                previous[neighbor->index] = current;
                queue[queue_size++] = neighbor;
            }
            
            edge = edge->next;
        }
    }

    /* If the target vertex is unreachable, return NULL */
    if (distances[target_index] == INT_MAX) {
        free(distances);
        free(previous);
        free(visited);
        return NULL;
    }

    /* Reconstruct the path from the target vertex to the start vertex */
    vertex_t *current = target;
    while (current != NULL) {
        queue_push_front(path, current->content);
        current = previous[current->index];
    }

    /* Clean up */
    free(distances);
    free(previous);
    free(visited);

    return path;
}
