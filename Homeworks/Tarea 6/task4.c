/**
    ANSI C standard: c11
    task4.c
    Purpose: Example to use a Stack (the stack works with two queues)

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


int main(int argc, char const *argv[]) {
    int size = 10;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    Stack stack = stack_create(size);

    for (int i = 0; i < size; i++) {
        printf("Push: %d\n", data[i]);
        stack_push(&stack, data[i]);
    }

    while(!stack_empty(stack)) {
        int top = stack_top(&stack);
        printf("Top-Pop %d\n", top);
        stack_pop(&stack);
    }

    stack_free(&stack);

    return 0;
}
