#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stddef.h>

/* Structure definitions */
typedef struct point_s
{
    int x;
    int y;
} point_t;

typedef struct vertex_s
{
    char *name;
    struct edge_s *edges;
    size_t num_edges;
} vertex_t;

typedef struct edge_s
{
    vertex_t *vertex;
    int weight;
} edge_t;

typedef struct graph_s
{
    vertex_t **vertices;
    size_t num_vertices;
} graph_t;

typedef struct queue_node_s
{
    void *item;
    struct queue_node_s *next;
} queue_node_t;

typedef struct queue_s
{
    queue_node_t *front;  /* Corrected type to queue_node_t * */
    queue_node_t *rear;   /* Corrected type to queue_node_t * */
} queue_t;

/* Function prototypes */
queue_t *create_queue(void);   /* Creates and returns a new queue */
void enqueue(queue_t *queue, void *item);  /* Adds an item to the queue */
void *dequeue(queue_t *queue); /* Removes and returns an item from the queue */

queue_t *backtracking_array(char **map, int rows, int cols,
                            point_t const *start, point_t const *target);
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start, vertex_t const *target);
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start, vertex_t const *target);

#endif /* PATHFINDING_H */