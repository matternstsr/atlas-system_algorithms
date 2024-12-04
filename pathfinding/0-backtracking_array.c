#include <stdlib.h>
#include <stdio.h>
#include "pathfinding.h"

/**
 * is_valid_move - Checks if a move is within bounds and on a walkable cell.
 * 
 * @map: The maze (2D array).
 * @rows: The number of rows in the map.
 * @cols: The number of columns in the map.
 * @x: The x-coordinate to check.
 * @y: The y-coordinate to check.
 *
 * Return: 1 if the move is valid, 0 otherwise.
 */
static int is_valid_move(char **map, int rows, int cols, int x, int y)
{
    return (x >= 0 && x < rows && y >= 0 && y < cols && map[x][y] == '0');
}

/**
 * backtrack - Helper function that performs backtracking to find a path.
 *
 * @map: The maze (2D array).
 * @rows: The number of rows in the map.
 * @cols: The number of columns in the map.
 * @start: The starting point coordinates.
 * @target: The target point coordinates.
 * @path: The queue to store the path.
 * @visited: 2D array to track visited cells.
 *
 * Return: 1 if a path is found, 0 otherwise.
 */
static int backtrack(char **map, int rows, int cols, point_t const *start, point_t const *target, queue_t *path, int **visited)
{
    int x = start->x;
    int y = start->y;

    // Check if we've reached the target
    if (x == target->x && y == target->y)
    {
        point_t *point = malloc(sizeof(point_t));
        if (!point)
            return 0;

        point->x = x;
        point->y = y;
        enqueue(path, point);
        return 1;
    }

    // Mark the current cell as visited
    visited[x][y] = 1;

    // Check the four possible directions: RIGHT, BOTTOM, LEFT, TOP
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (int i = 0; i < 4; i++)
    {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];

        if (is_valid_move(map, rows, cols, new_x, new_y) && !visited[new_x][new_y])
        {
            point_t next = {new_x, new_y};

            // Recursively explore the next cell
            if (backtrack(map, rows, cols, &next, target, path, visited))
            {
                point_t *point = malloc(sizeof(point_t));
                if (!point)
                    return 0;

                point->x = x;
                point->y = y;
                enqueue(path, point);
                return 1;
            }
        }
    }

    return 0;  // No path found
}

/**
 * backtracking_array - Searches for the first path from start to target using backtracking.
 *
 * @map: The maze (2D array).
 * @rows: The number of rows in the map.
 * @cols: The number of columns in the map.
 * @start: The starting point coordinates.
 * @target: The target point coordinates.
 *
 * Return: A queue containing the path from start to target, or NULL if no path is found.
 */
queue_t *backtracking_array(char **map, int rows, int cols, point_t const *start, point_t const *target)
{
    queue_t *path = create_queue();  // Create an empty queue for the path
    if (!path)
        return NULL;

    // Initialize a 2D visited array
    int **visited = malloc(rows * sizeof(int *));
    if (!visited)
    {
        free(path);
        return NULL;
    }
    for (int i = 0; i < rows; i++)
    {
        visited[i] = calloc(cols, sizeof(int));
        if (!visited[i])
        {
            for (int j = 0; j < i; j++)
                free(visited[j]);
            free(visited);
            free(path);
            return NULL;
        }
    }

    // Start backtracking from the starting point
    if (!backtrack(map, rows, cols, start, target, path, visited))
    {
        // No path found
        for (int i = 0; i < rows; i++)
            free(visited[i]);
        free(visited);
        free(path);
        return NULL;
    }

    // Free the visited array
    for (int i = 0; i < rows; i++)
        free(visited[i]);
    free(visited);

    return path;
}
