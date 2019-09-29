/**
    ANSI C standard: c11
    queue.c
    Purpose: Prototype for Queue implementation with two stacks

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include "stack.h"

typedef struct QueueStruct {
    int max_size;
    int front;
    Stack stacks[2];
} Queue;


/* Allocate memory for the queue */
extern Queue queue_create(int max_size);
/* Push a integer into the queue */
extern void queue_push(Queue * queue, int num);
/* Pop a integer into the queue */
extern int queue_pop(Queue * queue);
/* Get the first element from the queue */
extern int queue_front(Queue * queue);
/* Return 1 is the queue is empty zero otherwise */
extern int queue_empty(Queue queue);
/* Return que queue size */
extern int queue_size(Queue queue);
/* Liberate the memory allocated for the queue */
extern void queue_free(Queue * queue);
