#include <stdio.h>
#include "rb_trees.h"

void print_tree(rb_tree_t *tree) {
    if (tree) {
        printf("   .--%s(%03d)\n", (tree->color == RED) ? "R" : "B", tree->n);
        print_tree(tree->left);
        print_tree(tree->right);
    }
}

int main(void) {
    rb_tree_t *tree = NULL;
    int values[] = {43, 34, 65, 13, 46, 128, 256, 1, 624, 780};
    int num_values = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < num_values; i++) {
        rb_tree_t *new_node = rb_tree_insert(&tree, values[i]);
        if (new_node) {
            printf("Inserted: %d\n", values[i]);
            print_tree(tree);
        } else {
            printf("Failed to insert: %d\n", values[i]);
        }
    }

    return 0;
}
