#ifndef QUEUES_H
#define QUEUES_H

#include "pathfinding.h"

/* Function declarations for queue operations */

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

#endif /* QUEUES_H */
