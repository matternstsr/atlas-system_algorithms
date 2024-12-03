#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>

queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
                        vertex_t const *target)
{
    /* Implement Dijkstra's algorithm here */
    queue_t *path = create_queue();

    if (!path)
        return (NULL);

    /* Pretend the path is found to the target */
    char *city_name = strdup(start->name);

    enqueue(path, city_name);
    enqueue(path, strdup(target->name));

    return (path);
}
