#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stddef.h>

/* Edge types (e.g., bidirectional) */
#define BIDIRECTIONAL 1
#define UNIDIRECTIONAL 0

/**
* struct point_s - Structure storing coordinates
* @x: X coordinate
* @y: Y coordinate
*/
typedef struct point_s
{
	int x;
	int y;
} point_t;

/**
* struct vertex_s - Structure storing a vertex in the graph
* @name: Name of the vertex
* @edges: List of edges connected to this vertex
* @num_edges: List of edges connected to this vertex
*/
typedef struct vertex_s
{
	char *name;
	struct edge_s *edges;
	size_t num_edges;
	int x, y;    // Position or additional data
} vertex_t;

/**
* struct edge_s - Structure for an edge in the graph
* @vertex: The vertex the edge connects to
* @weight: The weight of the edge (distance or cost)
*/
typedef struct edge_s
{
	vertex_t *vertex;
	int weight;
} edge_t;

/**
* struct graph_s - Structure representing the graph
* @vertices: List of vertices in the graph
* @num_vertices: Number of vertices in the graph
*/
typedef struct graph_s
{
	vertex_t **vertices;
	size_t num_vertices;
} graph_t;

/**
* struct queue_node - Node in the queue structure
* @data: Data stored in the node
* @next: Pointer to the next node
*/
typedef struct queue_node
{
	void *data;
	struct queue_node *next;
} queue_node_t;

/**
* struct queue_s - Structure for a queue
* @front: Pointer to the front of the queue
* @rear: Pointer to the rear of the queue
*/
typedef struct queue_s
{
	queue_node_t *front;
	queue_node_t *rear;
} queue_t;

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

/**
 * create_queue - Creates and initializes an empty queue.
 * Return: A ptr to newly created queue, or NULL if memory allocation fails.
 */
queue_t *create_queue(void);   /* Declare create_queue() */

/**
 * enqueue - Adds a new element to the rear of the queue.
 * @queue: The queue to which the data will be added.
 * @data: A pointer to the data to be added to the queue.
 */
void enqueue(queue_t *queue, void *data);  /* Declare enqueue() */
/**
 * dequeue - Removes and returns the element from the front of the queue.
 * @queue: The queue from which the data will be removed.
 * Return: A ptr to data removed from front of queue or NULL if queue is empty.
 */
void *dequeue(queue_t *queue);  /* Declare dequeue() */

#endif /* PATHFINDING_H */
