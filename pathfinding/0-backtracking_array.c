#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Function prototype for backtrack
 */
int backtrack(char **map, char **visited, int rows, int cols, 
              int x, int y, point_t const *target, queue_t *path);

/**
 * backtracking_array - Searches for the first path from a starting point 
 * to a target point within a 2D array using backtracking
 * @map: Read-only two-dimensional array
 * @rows: Number of rows in the map
 * @cols: Number of columns in the map
 * @start: Starting point coordinates
 * @target: Target point coordinates
 * Return: Queue containing the path from start to target
 */
queue_t *backtracking_array(char **map, int rows, int cols, 
                            point_t const *start, point_t const *target)
{
    // Check for out of bounds
    if (start->x < 0 || start->x >= rows || start->y < 0 || start->y >= cols)
        return NULL;
    if (target->x < 0 || target->x >= rows || target->y < 0 || target->y >= cols)
        return NULL;

    // Create a map copy to track visited cells
    char **visited = malloc(rows * sizeof(char *));
    if (!visited) return NULL;

    for (int i = 0; i < rows; i++)
    {
        visited[i] = malloc(cols * sizeof(char));
        if (!visited[i])
        {
            // Free previously allocated memory
            for (int j = 0; j < i; j++)
                free(visited[j]);
            free(visited);
            return NULL;
        }
        // Copy the original map to preserve its content
        for (int j = 0; j < cols; j++)
            visited[i][j] = map[i][j];
    }

    // Create the path queue
    queue_t *path = create_queue();
    if (!path)
    {
        // Free visited map memory
        for (int i = 0; i < rows; i++)
            free(visited[i]);
        free(visited);
        return NULL;
    }

    // Call the backtracking function
    if (backtrack(map, visited, rows, cols, start->x, start->y, target, path) == 0)
    {
        // No path found
        free(path);
        path = NULL;
    }

    // Free visited map memory
    for (int i = 0; i < rows; i++)
        free(visited[i]);
    free(visited);

    return path;
}

/**
 * backtrack - The backtracking function that searches for the path recursively
 * @map: Read-only two-dimensional array representing the map
 * @visited: 2D array keeping track of visited cells
 * @rows: Number of rows in the map
 * @cols: Number of columns in the map
 * @x: Current X coordinate
 * @y: Current Y coordinate
 * @target: Target point coordinates
 * @path: The queue to store the path
 * Return: 1 if a path is found, 0 if no path is found
 */
int backtrack(char **map, char **visited, int rows, int cols, 
              int x, int y, point_t const *target, queue_t *path)
{
    // Print the current coordinates being checked
    printf("Checking coordinates [%d, %d]\n", x, y);

    // Check for out-of-bounds coordinates (valid range: 0 <= x < rows, 0 <= y < cols)
    if (x < 0 || x >= rows || y < 0 || y >= cols)
        return 0;

    // Check if the current cell is already visited or blocked (assuming '1' means visited)
    if (visited[x][y] == '1')
        return 0;

    // Mark current cell as visited
    visited[x][y] = '1';

    // Check if the target has been reached
    if (x == target->x && y == target->y)
    {
        // Create a new point and add to the path queue
        point_t *point = malloc(sizeof(point_t));
        if (!point) return 0;  // Memory allocation failure
        point->x = x;
        point->y = y;
        enqueue(path, point);  // Add the target to the path
        return 1;
    }

    // Add current point to path queue to ensure correct order (from start to target)
    point_t *point = malloc(sizeof(point_t));
    if (!point) return 0;  // Memory allocation failure
    point->x = x;
    point->y = y;
    enqueue(path, point);  // Add the current position to the path

    // Define the neighbor exploration order: RIGHT, BOTTOM, LEFT, TOP
    point_t neighbors[4] = {
        {x, y + 1},  // RIGHT
        {x + 1, y},  // BOTTOM
        {x, y - 1},  // LEFT
        {x - 1, y}   // TOP
    };

    // Explore each neighbor recursively
    for (int i = 0; i < 4; i++)
    {
        if (backtrack(map, visited, rows, cols, neighbors[i].x, neighbors[i].y, target, path))
        {
            return 1;  // Path has been found, no need to continue
        }
    }

    // If no valid path is found, remove the current point from the path
    free(dequeue(path));  // Remove the last added point

    return 0;  // No path found from this position
}





queue_t *create_queue(void)
{
    queue_t *queue = malloc(sizeof(queue_t));
    if (!queue)
        return NULL;
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(queue_t *queue, void *data)
{
    if (!queue)
        return;
    queue_node_t *new_node = malloc(sizeof(queue_node_t));
    if (!new_node)
        return;
    new_node->data = data;
    new_node->next = NULL;

    if (queue->rear)
        queue->rear->next = new_node;
    else
        queue->front = new_node;
    queue->rear = new_node;
}

void *dequeue(queue_t *queue)
{
    if (!queue || !queue->front)
        return NULL;
    queue_node_t *node = queue->front;
    void *data = node->data;
    queue->front = node->next;
    if (!queue->front)
        queue->rear = NULL;
    free(node);
    return data;
}




/*complies but bad data */