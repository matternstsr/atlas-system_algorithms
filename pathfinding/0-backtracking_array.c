#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>

static int explore_cell(char **map, int rows, int cols,
                        point_t const *current, point_t const *target,
                        queue_t *path, char **visited);

/**
 * backtracking_array - Finds the path from start to target.
 * @map: The map representing the grid.
 * @rows: The number of rows in the map.
 * @cols: The number of columns in the map.
 * @start: The start point.
 * @target: The target point.
 *
 * Return: A queue containing the path or NULL if no path is found.
 */
queue_t *backtracking_array(char **map, int rows, int cols,
                            point_t const *start, point_t const *target)
{
    queue_t *path = create_queue();
    if (!path) {
        printf("Failed to create queue\n");
        return NULL;
    }

    /* Create a visited array to mark visited cells */
    char **visited = malloc(rows * sizeof(char *));
    if (!visited) {
        printf("Failed to allocate memory for visited array\n");
        free(path);
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        visited[i] = calloc(cols, sizeof(char)); /* Initialize with 0 (unvisited) */
        if (!visited[i]) {
            printf("Failed to allocate memory for visited array row\n");
            free(visited);
            free(path);
            return NULL;
        }
    }

    /* Start exploring the map */
    if (explore_cell(map, rows, cols, start, target, path, visited)) {
        /* No need to reverse the order of the path here, it’s in the correct order */
        /* Free visited memory */
        for (int i = 0; i < rows; i++) {
            free(visited[i]);
        }
        free(visited);

        return path;
    }

    /* If no path is found, free memory and return NULL */
    for (int i = 0; i < rows; i++) {
        free(visited[i]);
    }
    free(visited);
    free(path);
    printf("Path not found\n");
    return NULL;
}

/**
 * explore_cell - Recursively explore each cell for the target.
 * @map: The map representing the grid.
 * @rows: The number of rows in the map.
 * @cols: The number of columns in the map.
 * @current: The current position being explored.
 * @target: The target position to reach.
 * @path: The queue to store the found path.
 * @visited: A 2D array that marks visited cells.
 *
 * Return: 1 if the target is found, 0 otherwise.
 */
static int explore_cell(char **map, int rows, int cols,
                        point_t const *current, point_t const *target,
                        queue_t *path, char **visited)
{
    /* Boundary conditions: out of bounds or already visited */
    if (current->x < 0 || current->x >= rows || current->y < 0 ||
        current->y >= cols || map[current->x][current->y] == '1' ||
        visited[current->x][current->y]) {
        return 0;
    }

    /* Debugging output to show current exploration */
    printf("Checking coordinates [%d, %d]\n", current->x, current->y);

    /* If the target is found */
    if (current->x == target->x && current->y == target->y) {
        point_t *new_point = malloc(sizeof(point_t));
        if (!new_point) {
            printf("Failed to allocate memory for new_point\n");
            return 0;
        }

        *new_point = *current;
        enqueue(path, new_point);

        /* Print the path found so far */
        return 1;
    }

    /* Mark the current cell as visited */
    visited[current->x][current->y] = 1;

    /* Define the neighbors (right, down, left, up) */
    point_t neighbors[4] = {
        {current->x, current->y + 1},  /* Right */
        {current->x + 1, current->y},  /* Down */
        {current->x, current->y - 1},  /* Left */
        {current->x - 1, current->y}   /* Up */
    };

    /* Explore all neighbors */
    for (int i = 0; i < 4; i++) {
        if (explore_cell(map, rows, cols, &neighbors[i], target, path, visited)) {
            point_t *new_point = malloc(sizeof(point_t));
            if (!new_point) {
                printf("Failed to allocate memory for new_point\n");
                return 0;
            }
            *new_point = *current;
            enqueue(path, new_point);
            return 1;
        }
    }

    /* If no path found, return 0 */
    return 0;
}

/**
 * create_queue - Creates and initializes a new queue.
 *
 * Return: A pointer to the new queue or NULL on failure.
 */
queue_t *create_queue(void)
{
    queue_t *queue = malloc(sizeof(queue_t));
    if (!queue) {
        printf("Failed to allocate memory for queue\n");
        return NULL;
    }
    queue->front = queue->rear = NULL;
    return queue;
}

/**
 * enqueue - Adds an item to the queue.
 * @queue: The queue to add the item to.
 * @item: The item to add to the queue.
 */
void enqueue(queue_t *queue, void *item)
{
    if (!queue) return;

    queue_node_t *node = malloc(sizeof(queue_node_t));
    if (!node) {
        printf("Failed to allocate memory for queue node\n");
        return;
    }

    node->item = item;
    node->next = NULL;

    if (queue->rear) {
        queue->rear->next = node;
        queue->rear = node;
    } else {
        queue->front = queue->rear = node;
    }
}

/**
 * dequeue - Removes and returns an item from the queue.
 * @queue: The queue to dequeue from.
 *
 * Return: The dequeued item or NULL if the queue is empty.
 */
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
