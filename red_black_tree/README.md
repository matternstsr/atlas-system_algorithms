# Red-Black Tree Implementation

This project implements a Red-Black Tree data structure in C. A Red-Black Tree is a balanced binary search tree with properties that ensure logarithmic time complexity for insertion, deletion, and search operations.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Functions](#functions)
- [Contributing](#contributing)
- [License](#license)

## Features

- Insertion and deletion of nodes
- Validation of Red-Black Tree properties
- Conversion of an array to a Red-Black Tree
- Efficient search operations

## Installation

To compile the project, you can use `gcc`:

```bash
gcc -o rb_tree rb_tree.c -Wall -Wextra
```

```c

#include "rb_trees.h"

int main() {
    /* Initialize the red-black tree to NULL */
    rb_tree_t *tree = NULL;
    
    /* Define an array of integers */
    int array[] = {10, 20, 30, 40, 50};

    /* Convert an array to a Red-Black Tree */
    tree = array_to_rb_tree(array, sizeof(array) / sizeof(array[0]));

    /* Insert a new value into the tree */
    rb_tree_insert(&tree, 25);

    /* Remove a value from the tree */
    tree = rb_tree_remove(tree, 30);

    /* Check if the tree is valid and print the result */
    if (rb_tree_is_valid(tree)) {
        printf("The tree is valid.\n");
    }

    return 0; /* Exit the program */
}
```



Make sure to replace the file name with the actual name of the Red-Black Tree implementation file.

## Usage

To use the Red-Black Tree implementation, include the header file in your C program:


## Functions

- `rb_tree_node`: Creates a new Red-Black Tree node.
- `rb_tree_insert`: Inserts a value into the tree.
- `rb_tree_remove`: Removes a value from the tree.
- `array_to_rb_tree`: Converts an array into a Red-Black Tree.
- `rb_tree_is_valid`: Checks if the tree maintains Red-Black properties.

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue for any enhancements or bug fixes.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.
