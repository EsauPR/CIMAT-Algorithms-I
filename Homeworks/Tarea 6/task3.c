/**
    ANSI C standard: c11
    task3.c
    Purpose: Example to use a Priority Queue

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"


int main(int argc, char const *argv[]) {
    // int size = 10;
    // int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = 11;
    int data[] = {20, 14, 11, 17, 14, 12, 13, 5, 6, 7, 8};

    PriorityQueue queue = priority_queue_create(size);

    for (int i = 0; i < size; i++) {
        printf("Enqueue %d\n", data[i]);
        priority_queue_push(&queue, data[i]);
    }

    puts("");

    while (!priority_queue_empty(queue)) {
        printf("Dequeue %d \n", priority_queue_pop(&queue));
    }

    priority_queue_free(&queue);

    return 0;
}
