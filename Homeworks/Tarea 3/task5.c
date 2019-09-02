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


void add_element(Node ** node, int num);
void print(Node * node);
void liberate(Node * node);
int get_kth_value(Node * node, int k);
int is_equal(Node * node1, Node * node2);


/*
    Insert and allocate memory for a
    new node at the beggining of the list
*/
void add_element(Node ** node, int num) {
    Node * tmp = (Node *)malloc(sizeof(Node));

    if (tmp == NULL) {
        perror("add_element(): ");
        return;
    }

    tmp->value = num;
    tmp->next = *node;
    *node = tmp;
}


/* Print the list elements */
void print(Node * node) {
    while(node != NULL) {
        printf("%d ", node->value);
        node = node->next;
    }
    puts("");
}


/* Free the memory list */
void liberate(Node * node) {
    Node * tmp;
    while(node != NULL) {
        tmp = node->next;
        free(node);
        node = tmp;
    }
}


/*
    Return the k-th value from a list
    If k is greater than the list size returns the value
    of the last element or zero if the list is empty
*/
int get_kth_value(Node * node, int k) {
    while(--k && node != NULL && node->next != NULL) {
        node = node->next;
    }

    if (node != NULL) {
        return node->value;
    }

    return 0;
}


/* Returns 1 if the lists are equals otherwise returns 0 */
int is_equal(Node * node1, Node * node2) {
    while(node1 != NULL && node2 != NULL) {
        if (node1->value != node2->value) {
            break;
        }
        node1 = node1->next;
        node2 = node2->next;
    }

    return node1 == node2;
}


int main(int argc, char const *argv[]) {
    Node * list1 = NULL;
    Node * list2 = NULL;
    Node * list3 = NULL;

    int ne = 100;

    // Generate list 1 and 2
    for (int i = 0; i < ne - 1; i++) {
        add_element(&list1, i);
        add_element(&list2, i);
    }
    puts("List 1:");
    print(list1);

    puts("List 2:");
    print(list2);

    // Generate list 3
    for (int i = 0; i < ne; i++) {
        add_element(&list3, i);
    }
    puts("List 3:");
    print(list3);

    // compare lists
    if(is_equal(list1, list2)) {
        puts("The lists 1 and 2 are equals");
    } else {
        puts("The lists 1 and 2 are not equal");
    }

    // compare lists
    if(is_equal(list1, list3)) {
        puts("The lists 1 and 3 are equals");
    } else {
        puts("The lists 1 and 3 are not equal");
    }

    //  Get the k-th element
    printf("The %d-th element for list 1 is: %d\n", 1, get_kth_value(list1, 1));
    printf("The %d-th element for list 2 is: %d\n", 100, get_kth_value(list2, 100));

    liberate(list1);
    liberate(list2);
    liberate(list3);

    return 0;
}
