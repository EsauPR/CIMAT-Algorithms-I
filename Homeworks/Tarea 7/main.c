/**
    ANSI C standard: c11
    main.c
    Purpose: Example of usage for black__red_tree.c module

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "red_black_tree.h"

int main(int argc, char const *argv[]) {
    Node * root = NULL;

    int ndata = 8;
    int data[] = {10, 20, -10, 15, 17, 40, 50, 60};

    for (int i = 0; i < ndata; i++) {
        printf("\nInsert %d\n", data[i]);
        tree_rb_insert(&root, NULL, data[i]);
        tree_rb_print(root);
    }

    // tree_rb_print(root);
    tree_rb_free(root);
    return 0;
}
