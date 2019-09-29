/**
    ANSI C standard: c11
    stack.c
    Purpose: Stack simulation with two queues

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include "stack.h"


/* Allocate memory for the stack */
Stack stack_create(int max_size) {
    Stack stack = {
        max_size,
        0,
        0,
        {queue_create(max_size), queue_create(max_size)}
    };

    return stack;
}

/* Push a integer into the stack */
void stack_push(Stack * stack, int num) {
    if (stack->size < stack->max_size){
        queue_push(&stack->queues[stack->index], num);
        stack->size ++;
    }
}

/* Pop a integer into the stack */
int stack_pop(Stack * stack) {
    if (stack_empty(*stack)) return -1;

    while(queue_size(stack->queues[stack->index]) > 1) {
        queue_push(&stack->queues[(stack->index + 1) % 2], queue_pop(&stack->queues[stack->index]));
    }

    int num = queue_pop(&stack->queues[stack->index]);
    stack->index = (stack->index + 1) % 2;
    stack->size --;
    return num;
}

/* Get the top element from the stack */
int stack_top(Stack * stack) {
    if (stack_empty(*stack)) return -1;

    int top = stack_pop(stack);
    stack_push(stack, top);
    return top;
}

/* Return 1 is the stack is empty zero otherwise */
int stack_empty(Stack stack) {
    return stack.size == 0;
}

/* Return que stack size */
int stack_size(Stack stack) {
    return stack.size;
}

/* Liberate the memory allocated for the stack */
void stack_free(Stack * stack) {
    stack->size = 0;
    queue_free(&stack->queues[0]);
    queue_free(&stack->queues[1]);
}
