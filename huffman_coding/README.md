# Huffman Coding

This repository contains an implementation of the **Huffman Coding** algorithm, which is a popular data compression technique. The project builds the Huffman tree from an array of symbols and their frequencies, then generates and prints the corresponding Huffman codes for each symbol.

### Table of Contents:
1. [Project Description](#project-description)
2. [Features](#features)
3. [File Structure](#file-structure)
4. [Installation](#installation)
5. [Usage](#usage)
6. [Function Descriptions](#function-descriptions)
7. [License](#license)

---

## Project Description

The goal of this project is to implement the **Huffman coding** algorithm. Huffman coding is used to compress data by assigning variable-length codes to symbols, where the most frequent symbols get the shortest codes. The algorithm uses a **priority queue** (implemented as a min-heap) to build a **Huffman tree**. The leaves of this tree represent the symbols, and traversing the tree generates the Huffman codes.

This project contains several functions that:
1. Create symbols and store their frequency.
2. Build a priority queue (min-heap) to store symbols.
3. Extract the two least frequent nodes from the heap, combine them into a new internal node, and insert it back into the heap.
4. Build the Huffman tree.
5. Generate and print the Huffman codes for each symbol.

---

## Features

- **Symbol Creation**: Create a symbol structure that stores a character and its associated frequency.
- **Priority Queue**: Build a priority queue (min-heap) using the symbols based on their frequencies.
- **Huffman Tree Construction**: Iteratively extract the least frequent nodes and combine them to form a Huffman tree.
- **Huffman Codes Generation**: Generate and print the Huffman codes for each symbol by traversing the Huffman tree.

---

## File Structure

The repository contains the following files:
```bash
.
├── README.md                # Project documentation
├── huffman.c                # Implementation of the Huffman coding functions
├── huffman.h                # Header file with function prototypes and structures
├── heap.c                   # Implementation of the heap (priority queue)
├── heap.h                   # Header file for heap functions
├── symbol.c                 # Implementation of the symbol creation
├── symbol.h                 # Header file for symbol-related structures
├── binary_tree_print.c      # Code for printing binary trees for visualization
├── binary_tree_print.h      # Header file for binary tree print functions
├── 5-main.c                 # Example for creating symbols
├── 6-main.c                 # Example for creating a priority queue
├── 7-main.c                 # Example for extracting and inserting nodes in the heap
├── 8-main.c                 # Example for building the Huffman tree
├── 9-main.c                 # Example for generating and printing Huffman codes
```

---

## Installation

To get started with the project, follow these steps:

1. Clone the repository to your local machine:

    ```bash
    git clone https://github.com/yourusername/huffman_coding.git
    cd huffman_coding
    ```

2. Compile the project:

    ```bash
    gcc -Wall -Wextra -Werror -pedantic -I./ *.c -o huffman
    ```

3. Run any of the example programs, for example:

    ```bash
    ./5-main
    ```

---

## Usage

The project provides a series of example programs to demonstrate the functionality of each stage of the Huffman coding process:

1. **Symbol Creation**: `5-main.c`
    - This example creates symbols using `symbol_create()` with specified data and frequency.

2. **Priority Queue**: `6-main.c`
    - This example builds the priority queue (min-heap) from a set of symbols and their frequencies.

3. **Extract and Insert**: `7-main.c`
    - This example demonstrates the process of extracting the two least frequent nodes from the heap and inserting a new internal node.

4. **Building the Huffman Tree**: `8-main.c`
    - This example constructs the Huffman tree by repeatedly extracting and inserting nodes until only one node remains in the priority queue.

5. **Huffman Codes**: `9-main.c`
    - This example generates the Huffman codes for each symbol by traversing the Huffman tree and prints them.

To run a specific example, use the following command:

```bash
./<example-file>
```
For example, to run the Huffman codes generation:
```bash
./9-main
```
Function Descriptions
symbol_create
```bash
symbol_t *symbol_create(char data, size_t freq);
```
    Description: Creates a new symbol structure.
    Parameters:
        data: The character to store in the symbol structure.
        freq: The frequency associated with the character.
    Returns: A pointer to the newly created symbol structure, or NULL if memory allocation fails.

huffman_priority_queue
```bash
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);
```
    Description: Creates a priority queue (min-heap) for Huffman coding.
    Parameters:
        data: An array of characters.
        freq: An array of frequencies corresponding to each character in data.
        size: The number of elements in data and freq.
    Returns: A pointer to the created priority queue, or NULL if the creation fails.

huffman_extract_and_insert
```bash
int huffman_extract_and_insert(heap_t *priority_queue);
```
    Description: Extracts the two least frequent nodes from the priority queue, combines them into a new node, and inserts it back into the queue.
    Parameters:
        priority_queue: A pointer to the priority queue (min-heap).
    Returns: 1 if successful, 0 if an error occurs.

huffman_tree
```bash
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size);
```
    Description: Builds the Huffman tree by extracting and combining the least frequent nodes from the priority queue.
    Parameters:
        data: An array of characters.
        freq: An array of frequencies corresponding to each character in data.
        size: The number of elements in data and freq.
    Returns: A pointer to the root node of the Huffman tree, or NULL if the tree cannot be built.

huffman_codes
```bash
int huffman_codes(char *data, size_t *freq, size_t size);
```
    Description: Builds the Huffman tree and generates the Huffman codes for each symbol.
    Parameters:
        data: An array of characters.
        freq: An array of frequencies corresponding to each character in data.
        size: The number of elements in data and freq.
    Returns: 1 on success, 0 on failure.

## License

This project is licensed under the MIT License - see the LICENSE file for details.