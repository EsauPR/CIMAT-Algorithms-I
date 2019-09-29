/**
    ANSI C standard: c11
    heap.c
    Purpose: Ternary heap implementation

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

#define SWAP(a,b) {a = a ^ b; b = a ^ b; a = a ^ b;}
#define MIN(a, b) (((a) < (b))? (a): (b))


/* Return a struc type Heap with allocated memory */
Heap heap_create(int max_size) {
    Heap heap = {max_size, 0, NULL};

    heap.data = (int * )malloc((max_size + 1) * sizeof(int));
    if (heap.data == NULL) {
        perror("heap_create()");
        exit(EXIT_FAILURE);
    }

    return heap;
}

/* buttom up heapify process*/
static void buttom_up_heapify(int * data, int index) {
    int parent_index;

    while(1) {
        parent_index = (index + 1) / 3;
        if (parent_index == 0 || data[parent_index] >= data[index]) return;
        SWAP(data[parent_index], data[index]);
        index = parent_index;
    }
}

/* Insert a integer into the heap */
void heap_insert(Heap * heap, int num) {
    if (heap->size == heap->max_size) return;
    heap->data[++heap->size] = num;
    buttom_up_heapify(heap->data, heap->size);
}

/* top down heapify process */
static void top_down_heapify(int * data, int index, int size) {
    int child_index;

    while(1) {
        child_index = index * 3 - 1;
        if (child_index >= size) return;

        if (data[child_index] <= data[index] &&
            data[child_index + 1 ] <= data[index] &&
            data[child_index + 2] <= data[index]) break;

        int max_child_index = child_index;
        for (int i = child_index + 1; i <= MIN(child_index + 2, size) ; i++) {
            if(data[max_child_index] < data[i]) {
                max_child_index = i;
            }
        }

        SWAP(data[index], data[max_child_index]);
        index = max_child_index;
    }
}

/* Remove the max element from the heap */
int heap_remove_max(Heap * heap) {
    if (heap->size < 1) return 0;

    heap->data[0] = heap->data[1];
    heap->data[1] = heap->data[heap->size--];
    top_down_heapify(heap->data, 1, heap->size);

    return heap->data[0];
}

/* Liberate the head allocated memory  */
void headp_free(Heap * heap) {
    free(heap->data);
    heap->data = NULL;
    heap->size = 0;
}
