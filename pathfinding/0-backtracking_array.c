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
