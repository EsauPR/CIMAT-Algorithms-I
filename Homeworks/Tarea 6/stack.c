/**
    ANSI C standard: c11
    stack.c
    Purpose: fixed Stack implementation

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


/* Allocate memory for the stack */
Stack stack_create(int max_size) {
    Stack stack = {max_size, -1, NULL};

    stack.data = (int *)malloc(sizeof(int) * max_size);
    if (stack.data == NULL) {
        perror("stack_create()");
        exit(EXIT_FAILURE);
    }

    return stack;
}

/* Push a integer into the stack */
void stack_push(Stack * stack, int num) {
    if (stack->top < stack->max_size - 1){
        stack->data[++stack->top] = num;
    }
}

/* Pop a integer into the stack */
int stack_pop(Stack * stack) {
    if (stack_empty(*stack)) return -1;

    stack->top--;

    return stack->data[stack->top + 1];
}

/* Get the top element from the stack */
int stack_top(Stack  stack) {
    if (stack_empty(stack)) return -1;

    return stack.data[stack.top];
}

/* Return 1 is the stack is empty zero otherwise */
int stack_empty(Stack stack) {
    return stack.top == -1;
}

/* Return que stack size */
int stack_size(Stack stack) {
    return stack.top + 1;
}

/* Liberate the memory allocated for the stack */
void stack_free(Stack * stack) {
    stack->top = -1;
    free(stack->data);
}
