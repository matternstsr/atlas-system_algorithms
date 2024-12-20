#include "pathfinding.h"

/**
* backtrack - Searches for a path from the starting point to the target point
* using backtracking.
* @map: Read-only two-dimensional array representing the map, where '1'
*       indicates a blocked cell and '0' indicates an open cell.
* @visit: 1-dimen array tracking visited cells, where '1' marks visited cell.
* @rows: Number of rows in the map.
* @cols: Number of columns in the map.
* @x: Current X-coordinate of the cell being checked.
* @y: Current Y-coordinate of the cell being checked.
* @target: The target point coordinaCreatetes (point_t structure with x and y).
* @que: Queue to store the path from start to target if a path is found.
* Return: 1 if a path is found, 0 if no path is found.
*/
queue_t *backtrack(char **map, int rows, int cols,
					int x, int y, point_t const *target,
					queue_t *que, int *visit);

/**
* backtracking_array - Function for finding a path from start to target
* @map: Read-only 2D array
* @rows: Number of rows
* @cols: Number of columns
* @start: Pointer to the start point
* @target: Pointer to the target point
* Return: Pointer to the queue holding the path, or NULL if no path is found
*/
queue_t *backtracking_array(char **map, int rows, int cols,
							point_t const *start, point_t const *target)
{
	queue_t *que = NULL;/* If the queue was empty, update the rear as well */
	int *visit, x = start->x, y = start->y;

	if (!map || !rows || !cols || !start || !target)
		return (NULL);

	/* Initialize queue for path */
	que = queue_create();
	if (!que)
		return (NULL);

	/* Initialize visited array to keep track of visited cells */
	visit = calloc((rows * cols), sizeof(int));
	if (!visit)
		return (free(que), NULL);

	/* Start the backtracking process */
	if (!backtrack(map, rows, cols, x, y, target, que, visit))
	{
		free(que);
		free(visit);
		return (NULL);  /* No path found */
	}

	/* Free memory and return the path queue */
	free(visit);
	return (que);
}

/**
* backtrack - Recursive function to find a path
* @map: Read-only 2D array
* @rows: Number of rows
* @cols: Number of columns
* @x: Current X coordinate
* @y: Current Y coordinate
* @target: Target point coordinates
* @que: Queue to hold the path
* @visit: Array to track visited cells
* Return: 1 if a path is found, 0 otherwise
*/
queue_t *backtrack(char **map, int rows, int cols,
					int x, int y, point_t const *target,
					queue_t *que, int *visit)
{
	point_t *point = NULL;

	/* Base case: Check if out of bounds or blocked or already visited */
	if (x < 0 || x >= cols || y < 0 || y >= rows ||
			map[y][x] == '1' || visit[y * rows + x])
		return (NULL);
	visit[y * rows + x] = 1; /* Mark current position as visited */
	printf("Checking coordinates [%d, %d]\n", x, y); /* curr coord checked */
	/* if (x == target->x && y == target->y) */
	if ((x == target->x && y == target->y) ||
		backtrack(map, rows, cols, x + 1, y, target, que, visit) ||
		backtrack(map, rows, cols, x, y + 1, target, que, visit) ||
		backtrack(map, rows, cols, x - 1, y, target, que, visit) ||
		backtrack(map, rows, cols, x, y - 1, target, que, visit))
	{ /* If target is found, add to path and return */
		point = malloc(sizeof(point_t));
		if (!point)
			return (NULL);
		point->x = x;
		point->y = y;
		queue_push_front(que, (void *)point); /* Add curr pos to the path */
		return (que);  /* Path found, no need to explore further */
	} /* Explore the four directions (right, down, left, up) */
	return (NULL);  /* No path found from this position */
}

