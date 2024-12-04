#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 1000

typedef struct stack_node {
    point_t point;
    int depth;
    struct stack_node* next;
} stack_node_t;

typedef struct {
    stack_node_t* top;
} stack_t;

stack_t* create_stack(void);
void push(stack_t* stack, point_t point, int depth);
stack_node_t* pop(stack_t* stack);
int is_stack_empty(stack_t* stack);
void free_stack(stack_t* stack);

queue_t* backtracking_array(char** map, int rows, int cols, point_t const* start, point_t const* target) {
    stack_t* stack = create_stack();
    if (!stack) {
        printf("Stack creation failed.\n");
        return NULL;
    }

    queue_t* path = create_queue();
    if (!path) {
        printf("Queue creation failed.\n");
        free_stack(stack);
        return NULL;
    }

    push(stack, *start, 0);

    while (!is_stack_empty(stack)) {
        stack_node_t* current_node = pop(stack);
        point_t current = current_node->point;
        int depth = current_node->depth;
        free(current_node);

        printf("Checking coordinates [%d, %d] at depth %d\n", current.x, current.y, depth);

        if (current.x < 0 || current.x >= rows || current.y < 0 || current.y >= cols) {
            continue;
        }

        if (map[current.x][current.y] == '1') {
            continue;
        }

        if (current.x == target->x && current.y == target->y) {
            point_t* new_point = malloc(sizeof(point_t));
            if (!new_point) {
                printf("Memory allocation failure for new point.\n");
                free_stack(stack);
                return NULL;
            }
            *new_point = current;
            enqueue(path, new_point);
            printf("Path found: [%d, %d]\n", current.x, current.y);
            free_stack(stack);
            return path;
        }

        map[current.x][current.y] = '1';  // Mark as visited

        point_t neighbors[4] = {
            {current.x, current.y + 1},  // Right
            {current.x + 1, current.y},  // Down
            {current.x, current.y - 1},  // Left
            {current.x - 1, current.y}   // Up
        };

        for (int i = 0; i < 4; i++) {
            push(stack, neighbors[i], depth + 1);
        }
    }

    free_stack(stack);
    return NULL;  // No path found
}

stack_t* create_stack(void) {
    stack_t* stack = malloc(sizeof(stack_t));
    if (!stack) {
        printf("Memory allocation failure for stack.\n");
        return NULL;
    }
    stack->top = NULL;
    return stack;
}

void push(stack_t* stack, point_t point, int depth) {
    stack_node_t* new_node = malloc(sizeof(stack_node_t));
    if (!new_node) {
        printf("Memory allocation failure for stack node.\n");
        return;
    }
    new_node->point = point;
    new_node->depth = depth;
    new_node->next = stack->top;
    stack->top = new_node;
}

stack_node_t* pop(stack_t* stack) {
    if (is_stack_empty(stack)) {
        return NULL;
    }
    stack_node_t* top_node = stack->top;
    stack->top = top_node->next;
    return top_node;
}

int is_stack_empty(stack_t* stack) {
    return stack->top == NULL;
}

void free_stack(stack_t* stack) {
    while (!is_stack_empty(stack)) {
        stack_node_t* top_node = pop(stack);
        free(top_node);
    }
    free(stack);
}


queue_t *create_queue(void) {
    queue_t *queue = malloc(sizeof(queue_t));
    if (!queue) {
        printf("Memory allocation failure for queue.\n");
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(queue_t *queue, void *data) {
    queue_node_t *new_node = malloc(sizeof(queue_node_t));
    if (!new_node) {
        printf("Memory allocation failure for queue node.\n");
        return;
    }
    new_node->data = data;
    new_node->next = NULL;

    if (queue->rear) {
        queue->rear->next = new_node;
    }
    queue->rear = new_node;

    if (!queue->front) {
        queue->front = new_node;
    }
}

void *dequeue(queue_t *queue) {
    if (!queue || !queue->front) {
        return NULL;
    }

    queue_node_t *front_node = queue->front;
    void *data = front_node->data;
    queue->front = front_node->next;

    if (!queue->front) {
        queue->rear = NULL;
    }

    free(front_node);
    return data;
}
