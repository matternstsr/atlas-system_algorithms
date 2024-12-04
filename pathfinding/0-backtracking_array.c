#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>

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

    // Recursive backtracking helper function
    int backtrack(int x, int y, int depth)
    {
        // Print the current coordinates being checked
        printf("Checking coordinates [%d, %d]\n", x, y);

        // Check for out of bounds
        if (x < 0 || x >= rows || y < 0 || y >= cols)
            return 0;

        // Check for blocked or already visited cells
        if (visited[x][y] == '1')
            return 0;

        // Mark current cell as visited
        visited[x][y] = '1';

        // Check if target is reached
        if (x == target->x && y == target->y)
        {
            // Create point and add to path
            point_t *point = malloc(sizeof(point_t));
            if (!point) return 0;
            point->x = x;
            point->y = y;
            enqueue(path, point);
            return 1;
        }

        // Define neighbor exploration order: RIGHT, BOTTOM, LEFT, TOP
        point_t neighbors[4] = {
            {x, y + 1},     // RIGHT
            {x + 1, y},     // BOTTOM
            {x, y - 1},     // LEFT
            {x - 1, y}      // TOP
        };

        // Try each neighbor
        for (int i = 0; i < 4; i++)
        {
            if (backtrack(neighbors[i].x, neighbors[i].y, depth + 1))
            {
                // Create point and add to path
                point_t *point = malloc(sizeof(point_t));
                if (!point) return 0;
                point->x = x;
                point->y = y;
                enqueue(path, point);
                return 1;
            }
        }

        return 0;
    }

    // Call the backtracking function
    if (backtrack(start->x, start->y, 0) == 0)
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
