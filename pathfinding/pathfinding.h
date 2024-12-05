#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stddef.h>
#include "graphs.h"
#include "queues.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>


/* Edge types (e.g., bidirectional) */
#define BIDIRECTIONAL 1
#define UNIDIRECTIONAL 0

/**
* struct point_s - Structure storing coordinates
* @x: X coordinatequeue_push_front
* @y: Y coordinate
*/
typedef struct point_s
{
	int x;
	int y;
} point_t;

/**
* backtracking_array - Searches for the first path from a starting point to
*                      a target point within a 2D array using backtracking.
* @map: The map (2D array) representing the grid
* @rows: The number of rows in the grid
* @cols: The number of columns in the grid
* @start: The starting point
* @target: The target point
* Return: A queue containing the path, or NULL if no path is found
*/
queue_t *backtracking_array(char **map, int rows, int cols,
							point_t const *start,
							point_t const *target);

/**
* backtracking_graph - Searches for the first path from a starting vertex to
*                      a target vertex in a graph using backtracking.
* @graph: The graph to search through
* @start: The starting vertex
* @target: The target vertex
* Return: A queue containing the path, or NULL if no path is found
*/
queue_t *backtracking_graph(graph_t *graph,
							vertex_t const *start, vertex_t const *target);

/**
* dijkstra_graph - Searches for the shortest path from a starting vertex to
*                  a target vertex in a graph using Dijkstra's algorithm.
* @graph: The graph to search through
* @start: The starting vertex
* @target: The target vertex
* Return: A queue containing the path, or NULL if no path is found
*/
queue_t *dijkstra_graph(graph_t *graph,
						vertex_t const *start, vertex_t const *target);

#endif /* PATHFINDING_H */
