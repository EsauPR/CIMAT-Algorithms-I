/**
    ANSI C standard: c11
    task4.c
    Purpose: Linked list

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct  node * next;
} Node;


void print(Node * node) {
    if (node == NULL) {
        puts("");
        return;
    };
    printf("%d ", node->value);
    print(node->next);
}


void add_element(Node ** node, int num) {
    if (*node == NULL) {
        (*node) = (Node *)malloc(sizeof(Node));
        (*node)->value = num;
        (*node)->next = NULL;
        return;
    }

    add_element(&(*node)->next, num);
}


void liberate(Node * node) {
    if (node == NULL) {
        return;
    }
    liberate(node->next);
    free(node);
}


int get_kth_value(Node * node, int k) {
    if (node == NULL) {
        return 0;
    }

    if(k == 1) {
        return node->value;
    }

    return get_kth_value(node->next, k - 1);
}

int is_equal(Node * node1, Node * node2) {
    if (node1 == NULL && node2 == NULL) {
        return 1;
    }

    if (node1 == NULL && node2 != NULL) {
        return 0;
    }

    if (node1 != NULL && node2 == NULL) {
        return 0;
    }

    if (node1->value != node2->value) {
        return 0;
    }

    return is_equal(node1->next, node2->next);
}

int main(int argc, char const *argv[]) {
    Node * list = NULL;



    print(list);

    return 0;
}
