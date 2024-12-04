#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>

static int explore_cell(char **map, int rows, int cols,
                        point_t const *current, point_t const *target,
                        queue_t *path, int depth);  // Pass recursion depth

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
    {
        printf("Failed to create queue.\n"); // Debugging line
        return (NULL);
    }

    if (explore_cell(map, rows, cols, start, target, path, 0))
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
 * @depth: The recursion depth (used to avoid excessive recursion)
 *
 * Return: 1 if a path is found, otherwise 0.
 */
static int explore_cell(char **map, int rows, int cols,
                        point_t const *current, point_t const *target,
                        queue_t *path, int depth)
{
    // Preventing too deep recursion (stack overflow)
    if (depth > (rows * cols))
    {
        printf("Recursion depth too deep, aborting.\n");
        return 0;
    }

    // Debugging line to see the state of the current cell
    printf("Checking coordinates [%d, %d] at depth %d\n", current->x, current->y, depth);

    if (current->x < 0 || current->x >= rows || current->y < 0 || current->y >= cols)
    {
        printf("Out of bounds: [%d, %d]\n", current->x, current->y);  // Debugging line
        return 0;
    }

    if (map[current->x][current->y] == '1')  // Blocked cell check
    {
        printf("Blocked cell: [%d, %d]\n", current->x, current->y);  // Debugging line
        return 0;
    }

    if (current->x == target->x && current->y == target->y)
    {
        point_t *new_point = malloc(sizeof(point_t));
        if (!new_point)
        {
            printf("Memory allocation failure for new point.\n");  // Debugging line
            return 0;  // Check malloc failure
        }

        *new_point = *current;
        enqueue(path, new_point);

        printf("Path found: [%d, %d]\n", current->x, current->y);  // Debugging line
        return 1;  // Found path
    }

    map[current->x][current->y] = '1';  // Mark as visited

    // Directions to explore (Right, Down, Left, Up)
    point_t neighbors[4] = {
        {current->x, current->y + 1},  // Right
        {current->x + 1, current->y},  // Down
        {current->x, current->y - 1},  // Left
        {current->x - 1, current->y}   // Up
    };

    for (int i = 0; i < 4; i++)
    {
        if (explore_cell(map, rows, cols, &neighbors[i], target, path, depth + 1))
        {
            point_t *new_point = malloc(sizeof(point_t));
            if (!new_point)
            {
                printf("Memory allocation failure for new point.\n");  // Debugging line
                return 0;  // Check malloc failure
            }

            *new_point = *current;
            enqueue(path, new_point);
            return 1;
        }
    }

    return 0;  // No path found
}

queue_t *create_queue(void) {
    queue_t *queue = malloc(sizeof(queue_t));
    if (!queue)
    {
        printf("Memory allocation failure for queue.\n");  // Debugging line
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(queue_t *queue, void *data) {
    queue_node_t *new_node = malloc(sizeof(queue_node_t));
    if (!new_node)
    {
        printf("Memory allocation failure for queue node.\n");  // Debugging line
        return;  // Return if memory allocation fails
    }
    new_node->data = data;
    new_node->next = NULL;

    if (queue->rear)
        queue->rear->next = new_node;
    queue->rear = new_node;

    if (queue->front == NULL)  // If the queue was empty, new node is also the front
        queue->front = new_node;

    // Debugging line to show the enqueue action
    printf("Enqueued point: [%d, %d]\n", ((point_t *)data)->x, ((point_t *)data)->y);
}

void *dequeue(queue_t *queue) {
    if (!queue->front)  // Return NULL if the queue is empty
    {
        printf("Queue is empty, cannot dequeue.\n");  // Debugging line
        return NULL;
    }

    queue_node_t *temp_node = queue->front;
    void *data = temp_node->data;
    queue->front = temp_node->next;

    if (queue->front == NULL)  // If the queue becomes empty, set rear to NULL
        queue->rear = NULL;

    free(temp_node);
    return data;
}
