#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>  /* For size_t */
#include <stdbool.h> /* For bool type */
#include <stdlib.h>  /* For malloc, free */

/**
 * struct queue_s - A simple queue data structure.
 * 
 * @size: The number of items currently in the queue.
 * @capacity: The maximum number of items the queue can hold.
 * @items: An array of items in the queue, representing the queue's data.
 */
typedef struct queue_s {
    size_t size;        /* The number of items currently in the queue */
    size_t capacity;    /* The maximum number of items the queue can hold */
    void **items;       /* Pointer to the array of items (void pointers for flexibility) */
    size_t front;       /* The front index of the queue */
    size_t rear;        /* The rear index of the queue */
} queue_t;

/* Macro to get the size of the queue (number of elements in the queue) */
#define QUEUE_SIZE(q) ((q)->size)

/* Function prototypes for queue operations */
queue_t *queue_create(size_t capacity);
void queue_delete(queue_t *queue);
bool queue_is_empty(queue_t *queue);
bool queue_is_full(queue_t *queue);
void queue_enqueue(queue_t *queue, void *item);
void *queue_dequeue(queue_t *queue);

#endif /* QUEUE_H */
