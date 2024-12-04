#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>

static int explore_cell(char **map, int rows, int cols,
                        point_t const *current, point_t const *target,
                        queue_t *path);

/**
 * backtracking_array - Find a path from start to target using
 *                      recursive backtracking on a 2D array.
 * @map: The 2D array representing the map.
 * @rows: Number of rows in the map.
 * @cols: Number of columns in the map.
 * @start: The starting point.
 * @target: The target point.
 *
 * Return: A queue that has path from start to target, NULL if no path found.
 */
queue_t *backtracking_array(char **map, int rows, int cols,
                            point_t const *start, point_t const *target)
{
    queue_t *path = create_queue();

    if (!path)
        return (NULL);

    if (explore_cell(map, rows, cols, start, target, path))
        return (path);

    free(path);
    return (NULL);
}

/**
 * explore_cell - Recursively explores next cells in the array to find a path.
 * @map: The 2D array representing the map.
 * @rows: Number of rows in the map.
 * @cols: Number of columns in the map.
 * @current: The current point to explore.
 * @target: The target point to reach.
 * @path: The queue to store the path.
 *
 * Return: 1 if a path is found, otherwise 0.
 */
static int explore_cell(char **map, int rows, int cols,
                        point_t const *current, point_t const *target,
                        queue_t *path)
{
    if (current->x < 0 || current->x >= rows || current->y < 0 ||
        current->y >= cols || map[current->x][current->y] == '1')
        return (0);

    if (current->x == target->x && current->y == target->y)
    {
        point_t *new_point = malloc(sizeof(point_t));

        if (!new_point)
            return (0);

        *new_point = *current;

        enqueue(path, new_point);

        return (1);
    }
    map[current->x][current->y] = '1';  /* Mark as visited */
    point_t neighbors[4] = {
        {current->x, current->y + 1},  /* Right */
        {current->x + 1, current->y},  /* Down */
        {current->x, current->y - 1},  /* Left */
        {current->x - 1, current->y}   /* Up */
    };
    for (int i = 0; i < 4; i++)
    {
        if (explore_cell(map, rows, cols, &neighbors[i], target, path))
        {
            point_t *new_point = malloc(sizeof(point_t));

            if (!new_point)
                return (0);

            *new_point = *current;

            enqueue(path, new_point);
            return (1);
        }
    }
    return (0);
}

struct queue_node {
    void *data;
    struct queue_node *next;
};

struct queue_s {
    struct queue_node *front;
    struct queue_node *rear;
};

queue_t *create_queue(void) {
    queue_t *queue = malloc(sizeof(queue_t));
    if (!queue)
        return NULL;
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(queue_t *queue, void *data) {
    struct queue_node *new_node = malloc(sizeof(struct queue_node));
    if (!new_node)
        return;  // Return if memory allocation fails
    new_node->data = data;
    new_node->next = NULL;

    if (queue->rear)
        queue->rear->next = new_node;
    queue->rear = new_node;

    if (queue->front == NULL)  // If the queue was empty, new node is also the front
        queue->front = new_node;
}

void *dequeue(queue_t *queue) {
    if (!queue->front)  // Return NULL if the queue is empty
        return NULL;

    struct queue_node *temp_node = queue->front;
    void *data = temp_node->data;
    queue->front = temp_node->next;

    if (queue->front == NULL)  // If the queue is now empty, set rear to NULL
        queue->rear = NULL;

    free(temp_node);  // Free the dequeued node
    return data;
}
