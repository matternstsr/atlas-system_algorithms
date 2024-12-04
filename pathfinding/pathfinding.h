#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "queue.h"  // Include queue.h for the queue_t type

/**
 * struct point_s - Structure storing coordinates
 *
 * @x: X coordinate
 * @y: Y coordinate
 */
typedef struct point_s
{
    int x;
    int y;
} point_t;

/**
 * backtracking_array - Searches for the first path from the start point to the target point
 *                      within a two-dimensional array using backtracking.
 *
 * @map: Pointer to a read-only two-dimensional array representing the maze.
 * @rows: The number of rows in the array.
 * @cols: The number of columns in the array.
 * @start: A pointer to the starting coordinates.
 * @target: A pointer to the target coordinates.
 *
 * Return: A queue containing the path from start to target, or NULL if no path is found.
 */
queue_t *backtracking_array(char **map, int rows, int cols, point_t const *start, point_t const *target);

#endif /* PATHFINDING_H */
