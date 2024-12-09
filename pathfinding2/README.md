# Pathfinding Project

This project implements various pathfinding algorithms in C, including:

1. **Backtracking Algorithm** - A recursive backtracking solution for finding a path in both a 2D array and a graph.
2. **Dijkstra's Algorithm** - A solution for finding the shortest path in a graph using Dijkstra's algorithm.

## Algorithms Implemented

### 1. Backtracking (Array)
- **Description**: Finds a path from a starting point to a target point in a 2D grid using a backtracking approach.
- **Files**:
  - `0-backtracking_array.c`
  - `pathfinding.h`

### 2. Backtracking (Graph)
- **Description**: Uses recursive backtracking to find a path in a graph from a start vertex to a target vertex.
- **Files**:
  - `1-backtracking_graph.c`

### 3. Dijkstra's Algorithm
- **Description**: Finds the shortest path between two points in a graph.
- **Files**:
  - `2-dijkstra_graph.c`

## Compilation and Testing

All files can be compiled using the `gcc` compiler with the necessary flags and libraries. For example:

```bash
gcc -o 0-backtracking_array -Wall -Wextra -Werror -pedantic 0-main.c 0-backtracking_array.c -lqueues
./0-backtracking_array
```