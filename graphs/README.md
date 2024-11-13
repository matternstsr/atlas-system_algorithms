# Graph Data Structure Project

This project implements a basic **graph data structure** with functions to manage vertices, edges, and traversal operations. It includes functionality for **creating a graph**, **adding vertices and edges**, **performing depth-first and breadth-first traversals**, and **deleting the graph**.

The project is written in **C** and provides a simple, efficient way to model a graph using an adjacency list, supporting both unidirectional and bidirectional edges.

## Table of Contents

- [Overview](#overview)
- [Tasks](#tasks)
  - [Task 0: Create a Graph](#task-0-create-a-graph)
  - [Task 1: Add a Vertex](#task-1-add-a-vertex)
  - [Task 2: Add an Edge](#task-2-add-an-edge)
  - [Task 3: Delete the Graph](#task-3-delete-the-graph)
  - [Task 4: Depth-First Traversal](#task-4-depth-first-traversal)
  - [Task 5: Breadth-First Traversal](#task-5-breadth-first-traversal)
- [Compilation](#compilation)
- [Usage](#usage)
- [License](#license)

## Overview

This project implements a **graph** data structure where:
- A **graph** consists of **vertices** connected by **edges**.
- Each **vertex** has a **content** (a string) and an **index**.
- **Edges** can be **unidirectional** or **bidirectional**, connecting vertices.

The implementation allows users to:
- Create a graph.
- Add vertices and edges.
- Perform depth-first and breadth-first traversals.
- Delete the graph and free the memory.

## Tasks

### Task 0: Create a Graph

The `graph_create()` function initializes and allocates memory for a new graph structure. It returns a pointer to the newly created graph, or `NULL` if memory allocation fails.

```c
graph_t *graph_create(void);
```
### Task 1: Add a Vertex

The graph_add_vertex() function adds a vertex to the graph. The function takes a string str that is stored in the new vertex. If a vertex with the same string already exists, the function returns NULL to avoid duplicates.


```c
vertex_t *graph_add_vertex(graph_t *graph, const char *str);

```

### Task 2: Add an Edge

The graph_add_edge() function adds an edge between two vertices. It takes two vertex identifiers (src and dest), and the edge type (unidirectional or bidirectional). It returns 1 on success and 0 if the edge cannot be added (e.g., if either vertex is not found).

```c
int graph_add_edge(graph_t *graph, const char *src, const char *dest, edge_type_t type);

```

### Task 3: Delete the Graph

The graph_delete() function deletes the graph and frees all associated memory, including vertices, edges, and the graph structure itself.

```c
void graph_delete(graph_t *graph);

```
### Task 4: Depth-First Traversal

The depth_first_traverse() function performs a depth-first traversal (DFS) on the graph. It visits each vertex in the graph and calls a provided action function with the vertex and its depth in the traversal. The function returns the maximum depth encountered during the traversal.


```c
size_t depth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth));

```
### Task 5: Breadth-First Traversal

The breadth_first_traverse() function performs a breadth-first traversal (BFS) on the graph. It visits each vertex layer by layer, starting from the first vertex, and calls the action function with the vertex and its depth. The function returns the maximum depth of the graph.



```c
size_t breadth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth));

```

### Compilation

To compile the project, follow these steps:

    Clone the repository or download the project files.
    Use a C compiler to compile the source files. For example, using gcc:

```c
gcc -o graph_program main.c graph.c -lm

```

This will generate an executable named graph_program (or another name of your choice).
Compilation Flags

    -o <output_name>: Specifies the name of the output executable.
    -lm: Links the math library (if needed, for certain operations).

### Usage

After compiling the code, you can run the program to test its functionality. The main.c file provides a simple driver program that demonstrates how to use the graph API.

```c
./graph_program

```
### Example:


```c

#include "graphs.h"
#include <stdio.h>

void print_vertex(const vertex_t *v, size_t depth) {
    printf("Vertex: %s, Depth: %zu\n", v->content, depth);
}

int main() {
    graph_t *graph = graph_create();
    if (!graph) {
        fprintf(stderr, "Failed to create graph\n");
        return 1;
    }

    graph_add_vertex(graph, "A");
    graph_add_vertex(graph, "B");
    graph_add_vertex(graph, "C");

    graph_add_edge(graph, "A", "B", UNIDIRECTIONAL);
    graph_add_edge(graph, "B", "C", BIDIRECTIONAL);

    printf("Depth-First Traversal:\n");
    depth_first_traverse(graph, print_vertex);

    printf("\nBreadth-First Traversal:\n");
    breadth_first_traverse(graph, print_vertex);

    graph_delete(graph);
    return 0;
}

```
In this example, we:

    Create a graph.
    Add three vertices: "A", "B", and "C".
    Add edges between them.
    Perform depth-first and breadth-first traversals, printing the visited vertices and their depths.
    Delete the graph at the end.

### License

This project is licensed under the MIT License - see the LICENSE file for details.