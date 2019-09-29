/**
    ANSI C standard: c11
    queue.c
    Purpose: Queue implementation with two stacks

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include "queue.h"

/* Allocate memory for the queue */
Queue queue_create(int max_size) {
    Queue queue = {max_size, -1, {
        stack_create(max_size),
        stack_create(max_size)
    }};

    return queue;
}
/* Push a integer into the queue */
void queue_push(Queue * queue, int num) {
    if (queue->front == queue->max_size -1) return;

    stack_push(&queue->stacks[0], num);
    queue->front ++;
}


/* Pop a integer into the queue */
int queue_pop(Queue * queue) {
    if (queue_empty(*queue)) return -1;

    while(stack_size(queue->stacks[0]) > 1) {
        stack_push(&queue->stacks[1], stack_pop(&queue->stacks[0]));
    }

    int num = stack_pop(&queue->stacks[0]);

    while(!stack_empty(queue->stacks[1])) {
        stack_push(&queue->stacks[0], stack_pop(&queue->stacks[1]));
    }

    queue->front --;

    return num;
}

/* Get the first element from the queue */
int queue_front(Queue * queue) {
    if (queue_empty(*queue)) return -1;

    while(stack_size(queue->stacks[0]) > 1) {
        stack_push(&queue->stacks[1], stack_pop(&queue->stacks[0]));
    }

    int num = stack_pop(&queue->stacks[0]);
    stack_push(&queue->stacks[1], num);

    while(!stack_empty(queue->stacks[1])) {
        stack_push(&queue->stacks[0], stack_pop(&queue->stacks[1]));
    }

    return num;
}

/* Return 1 is the queue is empty zero otherwise */
int queue_empty(Queue queue) {
    return queue.front == -1;
}

/* Return que queue size */
int queue_size(Queue queue) {
    return queue.front + 1;
}

/* Liberate the memory allocated for the queue */
void queue_free(Queue * queue) {
    queue->front = -1;
    stack_free(&queue->stacks[0]);
    stack_free(&queue->stacks[1]);
}
