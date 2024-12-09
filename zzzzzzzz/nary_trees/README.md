# N-ary Trees Project

This repository contains solutions for the N-ary Trees project at Holberton School. The project focuses on learning how to implement, manipulate, and analyze N-ary trees in C.

## Project Overview

The goal of this project is to gain an understanding of **N-ary trees** and their common applications. By the end of this project, you should be able to:

- Define what an N-ary tree is.
- Describe common usage cases for N-ary trees.
- Implement N-ary trees in C in at least two different ways.
- Calculate the diameter of an N-ary tree.

### N-ary Tree Definition

An N-ary tree is a tree data structure where each node can have multiple children. The nodes are organized into a tree-like structure, where each node contains data, a reference to its parent node, and pointers to its children.

## Learning Objectives

### General Objectives

- **What is an N-ary tree?**
- **Common usage of N-ary trees.**
- **Representing an N-ary tree in C in multiple ways.**
- **Calculating the diameter of an N-ary tree.**

### Specific Requirements

- **Allowed editors:** vi, vim, emacs.
- **Compilation environment:** Ubuntu 20.04 LTS with gcc 9.4.0.
- **Code style:** Betty style (checked using betty-style.pl and betty-doc.pl).
- **No global variables.**
- **No more than 5 functions per file.**
- **Your code must use the standard C library.**
- **The header file `nary_trees.h` must include function prototypes.**

## Project Tasks

### Task 0: Insert
Write a function to insert a node into an N-ary tree.

```c
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str);
```
The function inserts a new node in the parent’s child linked list. It duplicates the provided string and returns a pointer to the created node, or `NULL` on failure.

### Task 1: Delete
Write a function to deallocate the entire N-ary tree.

```c
void nary_tree_delete(nary_tree_t *tree);
```

This function recursively deletes all nodes in the N-ary tree, freeing their memory.

### Task 2: Traversal
Write a function to traverse an N-ary tree, visiting each node.

```c
size_t nary_tree_traverse(nary_tree_t const *root, void (*action)(nary_tree_t const *node, size_t depth));
```

This function takes a pointer to the root of the tree and a pointer to a function (`action`) that will be called for each node. The function returns the deepest depth in the tree.

### Task 3: Diameter
Write a function to compute the diameter of an N-ary tree.

```c
size_t nary_tree_diameter(nary_tree_t const *root);
```

The diameter is the longest path between any two nodes in the tree.

### Task 4: Path Exists
Write a function that checks if a path exists in the N-ary tree.

```c
int path_exists(nary_tree_t const *root, char const * const *path);
```

This function checks if the specified path exists in the tree. The path is a NULL-terminated array of strings that represent the nodes along the path.

## Data Structures

Here’s the structure used for the N-ary tree:

```c
/**
* struct nary_tree_s - N-ary tree node structure
*
* @content: Content of the node
* @parent: Pointer to the parent node
* @nb_children: Number of children
* @children: Pointer to the head node of the children linked list
* @next: Pointer to the next child in the parent's children linked list
*/
typedef struct nary_tree_s
{
	char            *content;
	struct nary_tree_s  *parent;
	size_t          nb_children;
	struct nary_tree_s  *children;
	struct nary_tree_s  *next;
} nary_tree_t;
```

### Structure Explanation

- `content`: The string data stored in the node.
- `parent`: A pointer to the parent node.
- `nb_children`: The number of children this node has.
- `children`: A pointer to the first child node.
- `next`: A pointer to the next child node in the parent’s child list.

## How to Run

Clone the repository and compile the code as follows:

```bash
git clone https://github.com/matternstsr/atlas-system_algorithms.git
cd atlas-system_algorithms/nary_trees
gcc -Wall -Wextra -Werror -pedantic -o your_program your_file.c
```

After compilation, you can run your program with:

``bash
./your_program
```

## Author

- **Alexandre Gautier**, Software Engineer at Holberton School. (NOW atlas)

## Repository

GitHub repository: [atlas-system_algorithms](https://github.com/matternstsr/atlas-system_algorithms)
Directory: `nary_trees`

## License

This project is open-source and available under the [MIT License](LICENSE).