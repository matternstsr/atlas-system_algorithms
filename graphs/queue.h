#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>  /* For size_t */

/**
* struct queue_s - A simple queue data structure for storing pointers.
* 
* @size: The current number of items in the queue.
* @capacity: The maximum number of items the queue can hold.
* @front: The index of the front item in the queue.
* @rear: The index of the rear item in the queue.
* @data: Pointer to the array of items in the queue.
*/
typedef struct queue_s {
	size_t size;      /* The number of items currently in the queue */
	size_t capacity;  /* The maximum number of items the queue can hold */
	size_t front;     /* The index of the front item in the queue */
	size_t rear;      /* The index of the rear item in the queue */
	void **data;      /* Array of pointers to the items (e.g., vertices or other data) */
} queue_t;

/* Function prototypes */
queue_t *queue_create(size_t capacity);
int queue_enqueue(queue_t *queue, void *item);
void *queue_dequeue(queue_t *queue);
int queue_is_empty(queue_t *queue);
void queue_delete(queue_t *queue);

#endif /* QUEUE_H */
