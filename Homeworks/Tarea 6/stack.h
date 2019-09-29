/**
    ANSI C standard: c11
    stack.c
    Purpose: Prototype for Stack simulation with two queues

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include "queue.h"

typedef struct  StructStack {
    int max_size;
    int size;
    int index;
    Queue queues[2];
} Stack;

/* Allocate memory for the stack */
extern Stack stack_create(int max_size);
/* Push a integer into the stack */
extern void stack_push(Stack * stack, int num);
/* Pop a integer into the stack */
extern int stack_pop(Stack * stack);
/* Get the top element from the stack */
extern int stack_top(Stack * stack);
/* Return 1 is the stack is empty zero otherwise */
extern int stack_empty(Stack stack);
/* Return que stack size */
extern int stack_size(Stack stack);
/* Liberate the memory allocated for the stack */
extern void stack_free(Stack * stack);
