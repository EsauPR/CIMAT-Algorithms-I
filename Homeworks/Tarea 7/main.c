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

    int ndata = 12;
    int data[] = {50, 25, 10, 7, 6, 0, -3, -5, -8, -10, -33, -45};

    for (int i = 0; i < ndata; i++) {
        printf("\nInsert %d\n", data[i]);
        tree_rb_insert(&root, NULL, data[i]);
        tree_rb_print(root);
    }

    int nkeys = 3;
    int keys[] = {-1, 20, 5};

    puts("");
    for (int i = 0; i < nkeys; i++) {
        if(tree_rb_find(root, keys[i])) {
            printf("The key '%d' exists\n", keys[i]);
        } else {
            printf("The key '%d' does not exists\n", keys[i]);
        }
    }

    tree_rb_free(root);
    return 0;
}
