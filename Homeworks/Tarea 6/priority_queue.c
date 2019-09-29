/**
    ANSI C standard: c11
    priority_queue.c
    Purpose: Priority Queue implementation

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include "priority_queue.h"

/* Allocate memory for a priority queue */
PriorityQueue priority_queue_create(int max_size) {
    PriorityQueue queue = {max_size, 0, heap_create(max_size)};
    return queue;
}

/* Push an integer into the priority queue */
void priority_queue_push(PriorityQueue * queue, int num) {
    heap_insert(&queue->heap, num);
    queue->size ++;
}

/* Pop and return an element from the priority queue */
int priority_queue_empty(PriorityQueue queue) {
    return queue.size == 0;
}

/* Return the top element from priority queue */
int priority_queue_pop(PriorityQueue * queue) {
    if (queue->size == 0) return -1;
    int tmp = heap_remove_max(&queue->heap);
    queue->size --;

    return tmp;
}

/* Return 1 is the queue is empty zero otherwise */
int priority_queue_top(PriorityQueue queue) {
    if (queue.size == 0) return -1;
    return queue.heap.data[1];
}

/* Liberate the allocated memory for the priority queue */
void priority_queue_free(PriorityQueue * queue) {
    headp_free(&queue->heap);
    queue->size = 0;
}
