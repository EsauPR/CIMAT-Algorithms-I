/**
    ANSI C standard: c11
    priority_queue.c
    Purpose: Prototype for Priority Queue implementation

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include "heap.h"

typedef struct PriorityQueueStruct {
    unsigned int max_size;
    int size;
    Heap heap;
} PriorityQueue;

/* Allocate memory for a priority queue */
extern PriorityQueue priority_queue_create(int max_size);
/* Push an integer into the priority queue */
extern void priority_queue_push(PriorityQueue * queue, int data);
/* Pop and return an element from the priority queue */
extern int priority_queue_pop(PriorityQueue * queue);
/* Return the top element from priority queue */
extern int priority_queue_top(PriorityQueue queue);
/* Return 1 is the queue is empty zero otherwise */
extern int priority_queue_empty(PriorityQueue queue);
/* Liberate the allocated memory for the priority queue */
extern void priority_queue_free(PriorityQueue * queue);
