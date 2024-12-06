#include "pathfinding.h"

/**
* dijkstra_graph - Uses dijkstra method to find shortest path
* @graph: Graph to find path in
* @start: starting vertex
* @target: Target Vertex
* Return: Queue holding path or NULL
*/
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
						vertex_t const *target)
{
	queue_t *Nque = NULL;
	int *currvis, *currdist;
	vertex_t **prev, *vert = NULL;
	size_t i = 0;

	if (!graph || !start || !target)
		return (NULL);
	/* Allocate memory for queue and tracking arrays */
	Nque = calloc(1, sizeof(queue_t));
	if (!Nque)
		return (NULL);
	currvis = calloc(graph->nb_vertices, sizeof(int));
	if (!currvis)
		return (free(Nque), NULL);
	currdist = calloc(graph->nb_vertices, sizeof(int));
	if (!currdist)
		return (free(currvis), free(Nque), NULL);
	prev = calloc(graph->nb_vertices, sizeof(vertex_t *));
	if (!prev)
		return (free(currdist), free(currvis), free(Nque), NULL);
	/* Initialize distances to infinity, except start vertex */
	for (i = 0; i < graph->nb_vertices; i++)
		currdist[i] = INT_MAX;
	/* Call find_dist to calculate shortest paths */
	if (!find_dist(start, target, graph, currvis, currdist, prev))
	{
		free(prev), free(currdist), free(currvis), free(Nque);
		currvis = NULL, currdist = NULL, prev = NULL, Nque = NULL;
		return (NULL);
	}
	/* Reconstruct path from target to start using prev array */
	for (vert = prev[target->index]; prev[vert->index]; vert = prev[vert->index])
		queue_push_front(Nque, strdup(vert->content));
	/* Push start and target vertices into queue */
	queue_push_front(Nque, strdup(start->content));
	queue_push_back(Nque, strdup(target->content));
	/* Free dynamically allocated memory */
	free(prev), free(currdist), free(currvis);
	currvis = NULL, currdist = NULL, prev = NULL;
	return (Nque);
}

/**
* find_dist - Calculates distance from Start
* @start: starting node
* @target: Target vertex
* @graph: Graph to path
* @currvis: array to track if a node has been visited
* @currdist: array to track distance from Start
* @prev: array of pointer to track path
* Return: 1 on Success, 0 on fail.
*/
int find_dist(vertex_t const *start, vertex_t const *target, graph_t *graph,
			int *currvis, int *currdist, vertex_t **prev)
{
	int mindist = INT_MAX;
	vertex_t *vert = NULL, *node = NULL;
	edge_t *this_edge = NULL;

	currdist[start->index] = 0;
	/* Main loop to calculate shortest path distances */
	while (node != target)
	{
		mindist = INT_MAX, node = NULL;
		/* Find unvisited vertex with smallest distance */
		for (vert = graph->vertices; vert; vert = vert->next)
		{
			if (!currvis[vert->index] && currdist[vert->index] < mindist)
				mindist = currdist[vert->index], node = vert;
		}
		if (!node)
			break;
		currvis[node->index] = 1;
		/* Debug: print current vertex being checked and its distance */
		printf("Checking %s, distance from %s is %d\n", node->content,
			start->content, currdist[node->index]);
		/* Relax edges connected to current vertex */
		for (this_edge = node->edges; this_edge; this_edge = this_edge->next)
		{
			if (!currvis[this_edge->dest->index] &&
				currdist[this_edge->dest->index] >
				mindist + this_edge->weight)
			{
				currdist[this_edge->dest->index] = mindist + this_edge->weight;
				prev[this_edge->dest->index] = node;
			}
		}
	}
	/* If we haven't found target, return failure */
	if (!node || node != target)
		return (0);
	return (1);
}
