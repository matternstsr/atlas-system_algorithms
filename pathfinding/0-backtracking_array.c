#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>

static int explore_cell(char **map, int rows, int cols,
                        point_t const *current, point_t const *target,
                        queue_t *path);

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