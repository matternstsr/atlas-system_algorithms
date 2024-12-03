#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>

queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
                        vertex_t const *target)
{
    /* Implement Dijkstra's algorithm here */
    queue_t *path = create_queue();

    if (!path)
        return (NULL);

    /* Pretend the path is found to the target */
    char *city_name = strdup(start->name);

    enqueue(path, city_name);
    enqueue(path, strdup(target->name));

    return (path);
}

queue_t *create_queue(void)
{
    queue_t *queue = malloc(sizeof(queue_t));
    if (!queue)
        return NULL;
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(queue_t *queue, void *item)
{
    if (!queue) return;

    /* Create a new node */
    queue_node_t *node = malloc(sizeof(queue_node_t));
    if (!node) return;

    node->item = item;
    node->next = NULL;

    if (queue->rear)
    {
        queue->rear->next = node;
        queue->rear = node;
    }
    else
    {
        queue->front = queue->rear = node;
    }
}

void *dequeue(queue_t *queue)
{
    if (!queue || !queue->front)
        return NULL;

    queue_node_t *node = queue->front;
    void *item = node->item;
    queue->front = node->next;

    if (!queue->front)
        queue->rear = NULL;

    free(node);
    return item;
}
