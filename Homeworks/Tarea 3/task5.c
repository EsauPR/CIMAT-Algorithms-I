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


/*
    Insert and allocate memory for a
    new node at the end of the list
*/
void add_element(Node ** node, int num) {
    if (*node != NULL) {
        add_element(&(*node)->next, num);
        return;
    }

    *node = (Node *)malloc(sizeof(Node));

    if (*node == NULL) {
        perror("add_element(): ");
        return;
    }

    (*node)->value = num;
    (*node)->next = NULL;

    return;
}


/* Print the list elements */
void print(Node * node) {
    if (node == NULL) {
        puts("");
        return;
    };
    printf("%d -> ", node->value);
    print(node->next);
}


/* Free the memory list */
void liberate(Node * node) {
    if (node == NULL) {
        return;
    }
    liberate(node->next);
    free(node);
}


/* Return the k-th value from a list */
int get_kth_value(Node * node, int k) {
    if (node == NULL) {
        return 0;
    }

    if(k == 1) {
        return node->value;
    }

    return get_kth_value(node->next, k - 1);
}


/* Compare two list */
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
    Node * list1 = NULL;
    Node * list2 = NULL;

    int ne = 100;

    // Generate list 1
    for (int i = 0; i < ne - 1; i++) {
        add_element(&list1, i);
    }
    puts("List 1:");
    print(list1);

    // Generate list 2
    for (int i = 0; i < ne; i++) {
        add_element(&list2, i);
    }
    puts("List 2:");
    print(list2);

    // compare lists
    if(is_equal(list1, list2)) {
        puts("The lists are equals");
    } else {
        puts("The lists are not equal");
    }

    //  Get the k-th element
    printf("The %d-th element for list 1 is: %d\n", 30, get_kth_value(list1, 30));
    printf("The %d-th element for list 2 is: %d\n", 40, get_kth_value(list2, 40));

    liberate(list1);
    liberate(list2);

    return 0;
}
