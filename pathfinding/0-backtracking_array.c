#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>

/**
* backtrack - Searches for a path from the starting point to the target point
* using backtracking.
* @map: Read-only two-dimensional array representing the map, where '1'
*       indicates a blocked cell and '0' indicates an open cell.
* @isV: Two-dimensional array keeps track of visited cells (marked as '1').
* @rows: Number of rows in the map.
* @cols: Number of columns in the map.
* @x: Current X-coordinate (starting point's X position).
* @y: Current Y-coordinate (starting point's Y position).
* @target: The target point coordinates (point_t structure with x and y).
* @path: Queue to store the path from start to target, if a path is found.
* Return: 1 if a path is found, 0 if no path is found.
*/
int backtrack(char **map, char **isV, int rows, int cols,
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
{/* Check for out of bounds */
	if (start->x < 0 || start->x >= rows || start->y < 0 || start->y >= cols)
		return (NULL);
	if (target->x < 0 || target->x >= rows || target->y < 0 || target->y >= cols)
		return (NULL); /* Create a map copy to track isV cells */
	char **isV = malloc(rows * sizeof(char *));

	if (!isV)
	return (NULL);
	for (int i = 0; i < rows; i++)
	{
		isV[i] = malloc(cols * sizeof(char));
		if (!isV[i])
		{/* Free previously allocated memory */
			for (int j = 0; j < i; j++)
				free(isV[j]);
			free(isV);
			return (NULL);
		} /* Copy the original map to preserve its content */
		for (int j = 0; j < cols; j++)
			isV[i][j] = map[i][j];
	} /* Create the path queue */
	queue_t *path = create_queue();

	if (!path)
	{/* Free isV map memory */
		for (int i = 0; i < rows; i++)
			free(isV[i]);
		free(isV);
		return (NULL);
	} /* Call the backtracking function */
	if (backtrack(map, isV, rows, cols, start->x, start->y, target, path) == 0)
	{
		No path found
		free(path);
		path = (NULL);
	}	/* Free isV map memory */
	for (int i = 0; i < rows; i++)
		free(isV[i]);
	free(isV);
	return (path);
}

/**
* backtrack - The backtracking function that searches for the path recursively
* @map: Read-only two-dimensional array representing the map
* @isV: 2D array keeping track of isV cells
* @rows: Number of rows in the map
* @cols: Number of columns in the map
* @x: Current X coordinate
* @y: Current Y coordinate
* @target: Target point coordinates
* @path: The queue to store the path
* Return: 1 if a path is found, 0 if no path is found
*/
int backtrack(char **map, char **isV, int rows, int cols,
			int x, int y, point_t const *target, queue_t *path)
{
	/* Print the current coordinates being checked */
	printf("Checking coordinates [%d, %d]\n", x, y);

	if (x < 0 || x >= rows || y < 0 || y >= cols)
		return (0); /* Check oob coord (valid range:0<=x<rows,0<=y<cols) */
	if (isV[x][y] == '1')
		return (0); /* Check if cell isV or blocked ('1' means isV) */
	isV[x][y] = '1';/* Mark current cell as isV */
	if (x == target->x && y == target->y)/* Check if the target has reached */
	{
		point_t *point = malloc(sizeof(point_t)); /* make pt, add path queue */

		if (!point)
		return (0);  /* Memory allocation failure */
		point->x = x;
		point->y = y;
		enqueue(path, point);  /* Add the target to the path */
		return (1);
	}
	/* Add current pt to path queue for good order (from start to target) */
	point_t *point = malloc(sizeof(point_t));

	if (!point)
	return (0);  /* Memory allocation failure */
	point->x = x;
	point->y = y;
	enqueue(path, point);  /* Add the current position to the path */
	/* Define the neighbor exploration order: BOTTOM, RIGHT */
	point_t nbrs[2] = {
		{x + 1, y},  /* BOTTOM (move down) */
		{x, y + 1}   /* RIGHT (move right) */
	};
	for (int i = 0; i < 2; i++) /* Explore each neighbor recursively */
	{
		if (backtrack(map, isV, rows, cols, nbrs[i].x, nbrs[i].y, target, path))
			return (1);  /* Path has been found, no need to continue */
	} /* If no valid path is found, remove the current point from the path */
	free(dequeue(path));  /* Remove the last added point */
	return (0);  /* No path found from this position */
}




/**
 * create_queue - Creates a new empty queue.
 * Return: A pointer to the newly created queue, or NULL if allocation fails.
 */
queue_t *create_queue(void)
{
	queue_t *queue = malloc(sizeof(queue_t));

	if (!queue)
		return (NULL);
	queue->front = queue->rear = NULL;
	return (queue);
}
/**
 * enqueue - Adds data to the rear of the queue.
 * @queue: The queue to add the data to.
 * @data: The data to add to the queue.
 */
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
/**
 * dequeue - Removes and returns data from the front of the queue.
 * @queue: The queue to remove data from.
 * Return: The data removed from front of queue, or NULL if queue is empty.
 */
void *dequeue(queue_t *queue)
{
	if (!queue || !queue->front)
		return (NULL);
	queue_node_t *node = queue->front;

	void *data = node->data;

	queue->front = node->next;

	if (!queue->front)
		queue->rear = NULL;
	free(node);
	return (data);
}

/*complies but bad data */
