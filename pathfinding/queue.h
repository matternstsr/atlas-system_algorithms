#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

// Forward declaration of point_t (defined in pathfinding.h)
typedef struct point_s point_t;

/**
 * struct queue_node_s - Represents a node in the queue.
 * @point: A point in the path.
 * @next: Pointer to the next node in the queue.
 */
typedef struct queue_node_s
{
    point_t *point;          /* The point associated with this node */
    struct queue_node_s *next; /* Pointer to the next node in the queue */
} queue_node_t;

/**
 * struct queue_s - Represents a queue.
 * @front: Pointer to the front of the queue.
 * @rear: Pointer to the rear of the queue.
 */
typedef struct queue_s
{
    queue_node_t *front; /* Front of the queue */
    queue_node_t *rear;  /* Rear of the queue */
} queue_t;

/* Function declarations */

/**
 * create_queue - Creates and initializes a new queue.
 *
 * Return: A pointer to the new queue, or NULL on failure.
 */
queue_t *create_queue(void);

/**
 * enqueue - Adds a point to the queue.
 * 
 * @queue: The queue to which the point will be added.
 * @point: The point to add to the queue.
 *
 * Return: 1 on success, or 0 on failure.
 */
int enqueue(queue_t *queue, point_t *point);

/**
 * dequeue - Removes and returns the point at the front of the queue.
 *
 * @queue: The queue from which to dequeue a point.
 *
 * Return: A pointer to the dequeued point, or NULL if the queue is empty.
 */
point_t *dequeue(queue_t *queue);

/**
 * free_queue - Frees all memory associated with the queue.
 *
 * @queue: The queue to free.
 */
void free_queue(queue_t *queue);

#endif /* QUEUE_H */
