/**
    ANSI C standard: c11
    queue.c
    Purpose: Fixed Queue implementation

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "queue.h"

/* Allocate memory for the queue */
Queue queue_create(int max_size) {
    Queue queue = {max_size, -1, 0, NULL};
    queue.data = (int *)malloc(sizeof(int) * max_size);
    return queue;
}
/* Push a integer into the queue */
void queue_push(Queue * queue, int num) {
    int next = (queue->back + 1) % queue->max_size;
    if (queue->back != -1 && next == queue->front ) return;
    queue->back = next;
    queue->data[next] = num;
}


/* Pop a integer into the queue */
int queue_pop(Queue * queue) {
    if (queue_empty(*queue)) return -1;

    int num = queue->data[queue->front];

    if (queue->front == queue->back) {
        queue->back = -1;
        queue->front = 0;
    } else {
        queue->front = (queue->front + 1) % queue->max_size;
    }

    return num;
}

/* Get the first element from the queue */
int queue_front(Queue queue) {
    return queue.data[queue.front];
}

/* Return 1 is the queue is empty zero otherwise */
int queue_empty(Queue queue) {
    return queue.back == -1;
}

/* Return que queue size */
int queue_size(Queue queue) {
    int size = 0;

    if (queue.back == -1) {
        size = 0;
    }else if (queue.back >= queue.front) {
        size = queue.back - queue.front + 1;
    } else {
        size = queue.max_size - queue.front + queue.back + 1;
    }

    return size;
}

/* Liberate the memory allocated for the queue */
void queue_free(Queue * queue) {
    free(queue->data);
    queue->back = -1;
    queue->front = 0;
}
