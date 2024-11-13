#include "queue.h"
#include <stdlib.h>  /* For malloc, free */

/**
 * queue_create - Creates a new queue with the given capacity.
 * 
 * @capacity: The maximum number of items the queue can hold.
 * 
 * Return: A pointer to the newly created queue, or NULL if memory allocation fails.
 */
queue_t *queue_create(size_t capacity) {
    /* Allocate memory for the queue */
    queue_t *queue = malloc(sizeof(queue_t));
    if (!queue) {
        return NULL;  /* Memory allocation failed */
    }
    
    /* Initialize the queue's properties */
    queue->size = 0;
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = 0;
    
    /* Allocate memory for the data array */
    queue->data = malloc(capacity * sizeof(void *));
    if (!queue->data) {
        free(queue);  /* Free the queue memory if data allocation fails */
        return NULL;
    }

    return queue;  /* Return the newly created queue */
}

/**
 * queue_enqueue - Adds an item to the queue.
 * 
 * @queue: The queue to which the item will be added.
 * @item: The item (pointer) to add to the queue.
 * 
 * Return: 0 if the item was successfully added, or -1 if the queue is full.
 */
int queue_enqueue(queue_t *queue, void *item) {
    /* Check if the queue is full */
    if (queue->size == queue->capacity) {
        return -1;  /* The queue is full */
    }
    
    /* Add the item to the queue at the rear index */
    queue->data[queue->rear] = item;
    /* Update the rear index (circularly) */
    queue->rear = (queue->rear + 1) % queue->capacity;
    /* Increase the size of the queue */
    queue->size++;

    return 0;  /* Success */
}

/**
 * queue_dequeue - Removes an item from the front of the queue.
 * 
 * @queue: The queue from which the item will be removed.
 * 
 * Return: A pointer to the removed item, or NULL if the queue is empty.
 */
void *queue_dequeue(queue_t *queue) {
    /* Check if the queue is empty */
    if (queue->size == 0) {
        return NULL;  /* The queue is empty */
    }

    /* Get the item at the front of the queue */
    void *item = queue->data[queue->front];
    /* Update the front index (circularly) */
    queue->front = (queue->front + 1) % queue->capacity;
    /* Decrease the size of the queue */
    queue->size--;

    return item;  /* Return the dequeued item */
}

/**
 * queue_is_empty - Checks if the queue is empty.
 * 
 * @queue: The queue to check.
 * 
 * Return: 1 if the queue is empty, or 0 if the queue is not empty.
 */
int queue_is_empty(queue_t *queue) {
    return queue->size == 0;  /* Return true if the queue is empty */
}

/**
 * queue_delete - Deletes the queue and frees the allocated memory.
 * 
 * @queue: The queue to delete.
 */
void queue_delete(queue_t *queue) {
    if (queue) {
        /* Free the memory for the data array */
        free(queue->data);
        /* Free the memory for the queue itself */
        free(queue);
    }
}
