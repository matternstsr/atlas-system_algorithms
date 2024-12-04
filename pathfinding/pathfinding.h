#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stddef.h>
#include "queues.h"  // For queue_t
#include "graphs.h"  // For graph and vertex definitions

// Structure definitions for point and queue-related objects
typedef struct point_s
{
    int x;
    int y;
} point_t;

queue_t *backtracking_array(char **map, int rows, int cols,
                            point_t const *start, point_t const *target);

#endif /* PATHFINDING_H */
