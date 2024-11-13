#ifndef QUEUE_H
#define QUEUE_H

#include "graphs.h"  

/* queue structure */
typedef struct queue_s
{
    vertex_t **items;   /* Array of ptrs vertex_t (queue will hold vertices) */
    size_t capacity;    /* The maximum number of items the queue can hold */
    size_t front;       /* The index of the front of the queue */
    size_t rear;        /* The index of the rear of the queue */
    size_t size;        /* Current number of elements in the queue */
} queue_t;

/* Function declarations for queue operations */
queue_t *queue_create(size_t capacity);
void queue_delete(queue_t *queue);
int queue_enqueue(queue_t *queue, vertex_t *vertex);
vertex_t *queue_dequeue(queue_t *queue);
int queue_is_empty(queue_t *queue);
int queue_is_full(queue_t *queue);
size_t queue_size(queue_t *queue);

#endif /* QUEUE_H */
