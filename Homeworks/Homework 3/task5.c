/**
    ANSI C standard: c11
    task4.c
    Purpose: Linked list

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
​
typedef struct node {
    int value;
    struct  node * next;
} NODE;

​
void print(NODE * root) {
    if (root == NULL) {
        puts("");
        return;
    };
    printf("%d ", root->value);
    print(root->next);
}
​
​
void insert(NODE ** root, int num) {
    if (*root == NULL) {
        (*root) = new NODE();
        (*root)->value = num;
        return;
    }
​
    if (num <= (*root)->value) {
        insert(&(*root)->left, num);
    } else {
        insert(&(*root)->right, num);
    }
}
​
int main(int argc, char const *argv[]) {
    NODE * root = NULL;
    int nelems = 9;
    int elems_to_insert[nelems] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
​
    for (int i = 0; i < nelems; i++) {
        insert(&root, elems_to_insert[i]);
    }
​
    print(root);
    return 0;
}


int main(int argc, char const *argv[]) {

    return 0;
}
