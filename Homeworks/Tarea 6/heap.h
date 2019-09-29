/**
    ANSI C standard: c11
    heap.c
    Purpose: Prototype for ternary heap implementation

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

typedef struct HeapStruct {
    unsigned int max_size;
    int size;
    int * data;
} Heap;

/* Return a struc type Heap with allocated memory */
extern Heap heap_create(int max_size);
/* Insert a integer into the heap */
extern void heap_insert(Heap * heap, int data);
/* Remove the max element from the heap */
extern int heap_remove_max(Heap * heap);
/* Liberate the head allocated memory  */
extern void headp_free(Heap * heap);
