/**
    ANSI C standard: c11
    task4.c
    Purpose: Example to use a Queue (the queue works with two stacks)

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


int main(int argc, char const *argv[]) {
    int size = 10;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    Queue queue = queue_create(size);

    for (int i = 0; i < size; i++) {
        printf("Push: %d\n", data[i]);
        queue_push(&queue, data[i]);
    }

    while(!queue_empty(queue)) {
        printf("Front and pop %d\n", queue_front(&queue));
        queue_pop(&queue);
    }

    queue_free(&queue);

    return 0;
}
