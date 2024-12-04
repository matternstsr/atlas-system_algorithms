#include "queues.h"  // For queue_t
#include "graphs.h"  // For point_t
#include "pathfinding.h"


/**
 * reverse_queue - Reverses the order of the items in the queue.
 * @path: The queue to reverse.
 */
static void reverse_queue(queue_t *path)
{
    if (!path || !path->front)
        return;

    point_t *item;
    queue_t *reversed = create_queue();
    if (!reversed)
        return;

    // Reverse the items in the original queue and add them to the new queue
    while (path->front) {
        item = dequeue(path);
        enqueue(reversed, item);
    }

    // Move the reversed queue back to the original
    while (reversed->front) {
        item = dequeue(reversed);
        enqueue(path, item);
    }

    free(reversed);
}

/**
 * backtracking_array - Finds the path from start to target.
 * @map: The map representing the grid.
 * @rows: The number of rows in the map.
 * @cols: The number of columns in the map.
 * @start: The start point.
 * @target: The target point.
 *
 * Return: A queue containing the path or NULL if no path is found.
 */
queue_t *backtracking_array(char **map, int rows, int cols,
                            point_t const *start, point_t const *target)
{
    queue_t *path = create_queue();
/**
 * reverse_queue - Reverses the order of the items in the queue.
 * @path: The queue to reverse.
 */
static void reverse_queue(queue_t *path)
{
    if (!path || !path->front)
        return;

    point_t *item;
    queue_t *reversed = create_queue();
    if (!reversed)
        return;

    // Reverse the items in the original queue and add them to the new queue
    while (path->front) {
        item = dequeue(path);
        enqueue(reversed, item);
    }

    // Move the reversed queue back to the original
    while (reversed->front) {
        item = dequeue(reversed);
        enqueue(path, item);
    }

    free(reversed);
}

/**
 * backtracking_array - Finds the path from start to target.
 * @map: The map representing the grid.
 * @rows: The number of rows in the map.
 * @cols: The number of columns in the map.
 * @start: The start point.
 * @target: The target point.
 *
 * Return: A queue containing the path or NULL if no path is found.
 */
queue_t *backtracking_array(char **map, int rows, int cols,
                            point_t const *start, point_t const *target)
{
    queue_t *path = create_queue();
    if (!path) {
        printf("Failed to create queue\n");
        return NULL;
    }

    /* Create a visited array to mark visited cells */
    char **visited = malloc(rows * sizeof(char *));
    if (!visited) {
        printf("Failed to allocate memory for visited array\n");
        free(path);
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        visited[i] = calloc(cols, sizeof(char)); /* Initialize with 0 (unvisited) */
        if (!visited[i]) {
            printf("Failed to allocate memory for visited array row\n");
            free(visited);
            free(path);
            return NULL;
        }
    }

    /* Start exploring the map */
    if (explore_cell(map, rows, cols, start, target, path, visited)) {
        /* Reverse the queue to have the path in the correct order */
        reverse_queue(path);

        /* Free visited memory *//**
 * reverse_queue - Reverses the order of the items in the queue.
 * @path: The queue to reverse.
 */
static void reverse_queue(queue_t *path)
{
    if (!path || !path->front)
        return;

    point_t *item;
    queue_t *reversed = create_queue();
    if (!reversed)
        return;

    // Reverse the items in the original queue and add them to the new queue
    while (path->front) {
        item = dequeue(path);
        enqueue(reversed, item);
    }
/**
 * reverse_queue - Reverses the order of the items in the queue.
 * @path: The queue to reverse.
 */
static void reverse_queue(queue_t *path)
{
    if (!path || !path->front)
        return;

    point_t *item;
    queue_t *reversed = create_queue();
    if (!reversed)
        return;

    // Reverse the items in the original queue and add them to the new queue
    while (path->front) {
        item = dequeue(path);
        enqueue(reversed, item);
    }

    // Move the reversed queue back to the original
    while (reversed->front) {
        item = dequeue(reversed);
        enqueue(path, item);
    }

    free(reversed);
}

/**
 * backtracking_array - Finds the path from start to target.
 * @map: The map representing the grid.
 * @rows: The number of rows in the map.
 * @cols: The number of columns in the map.
 * @start: The start point.
 * @target: The target point.
 *
 * Return: A queue containing the path or NULL if no path is found.
 */
queue_t *backtracking_array(char **map, int rows, int cols,
                            point_t const *start, point_t const *target)
{
    queue_t *path = create_queue();
    if (!path) {
        printf("Failed to create queue\n");
        return NULL;
    }

    /* Create a visited array to mark visited cells */
    char **visited = malloc(rows * sizeof(char *));
    if (!visited) {
        printf("Failed to allocate memory for visited array\n");
        free(path);
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        visited[i] = calloc(cols, sizeof(char)); /* Initialize with 0 (unvisited) */
        if (!visited[i]) {
            printf("Failed to allocate memory for visited array row\n");
            free(visited);
            free(path);
            return NULL;
        }
    }

    /* Start exploring the map */
    if (explore_cell(map, rows, cols, start, target, path, visited)) {
        /* Reverse the queue to have the path in the correct order */
        reverse_queue(path);

        /* Free visited memory */
        for (int i = 0; i < rows; i++) {
            free(visited[i]);
        }
        free(visited);

        return path;  // Return the path after reversing
    }

    /* If no path is found, free memory and return NULL */
    for (int i = 0; i < rows; i++) {
        free(visited[i]);
    }
    free(visited);
    free(path);
    printf("Path not found\n");
    return NULL;
}

        item = dequeue(reversed);
        enqueue(path, item);
    }

    free(reversed);
}

/**
 * backtracking_array - Finds the path from start to target.
 * @map: The map representing the grid.
 * @rows: The number of rows in the map.
 * @cols: The number of columns in the map.
 * @start: The start point.
 * @target: The target point.
 *
 * Return: A queue containing the path or NULL if no path is found.
 */
queue_t *backtracking_array(char **map, int rows, int cols,
                            point_t const *start, point_t const *target)
{
    queue_t *path = create_queue();
    if (!path) {
        printf("Failed to create queue\n");
        return NULL;
    }

    /* Create a visited array to mark visited cells */
    char **visited = malloc(rows * sizeof(char *));
    if (!visited) {
        printf("Failed to allocate memory for visited array\n");
        free(path);
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        visited[i] = calloc(cols, sizeof(char)); /* Initialize with 0 (unvisited) */
        if (!visited[i]) {
            printf("Failed to allocate memory for visited array row\n");
            free(visited);
            free(path);
            return NULL;
        }
    }

    /* Start exploring the map */
    if (explore_cell(map, rows, cols, start, target, path, visited)) {
        /* Reverse the queue to have the path in the correct order */
        reverse_queue(path);

        /* Free visited memory */
        for (int i = 0; i < rows; i++) {
            free(visited[i]);
        }
        free(visited);

        return path;  // Return the path after reversing
    }

    /* If no path is found, free memory and return NULL */
    for (int i = 0; i < rows; i++) {
        free(visited[i]);
    }
    free(visited);
    free(path);
    printf("Path not found\n");
    return NULL;
}


        return path;  // Return the path after reversing
    }

    /* If no path is found, free memory and return NULL */
    for (int i = 0; i < rows; i++) {
        free(visited[i]);
    }
    free(visited);
    free(path);
    printf("Path not found\n");
    return NULL;
}


    /* Create a visited array to mark visited cells */
    char **visited = malloc(rows * sizeof(char *));
    if (!visited) {
        printf("Failed to allocate memory for visited array\n");
        free(path);
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        visited[i] = calloc(cols, sizeof(char)); /* Initialize with 0 (unvisited) */
        if (!visited[i]) {
            printf("Failed to allocate memory for visited array row\n");
            free(visited);
            free(path);
            return NULL;
        }
    }

    /* Start exploring the map */
    if (explore_cell(map, rows, cols, start, target, path, visited)) {
        /* Reverse the queue to have the path in the correct order */
        reverse_queue(path);

        /* Free visited memory */
        for (int i = 0; i < rows; i++) {
            free(visited[i]);
        }
        free(visited);

        return path;  // Return the path after reversing
    }

    /* If no path is found, free memory and return NULL */
    for (int i = 0; i < rows; i++) {
        free(visited[i]);
    }
    free(visited);
    free(path);
    printf("Path not found\n");
    return NULL;
}
