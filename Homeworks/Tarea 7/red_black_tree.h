/**
    ANSI C standard: c11
    balc_red_tree.c
    Purpose: Prototype for Black-Red Tree module

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

/* Struct for Red-Black Node */
typedef struct structNode {
    struct structNode * parent;
    struct structNode * left;
    struct structNode * right;
    unsigned int color;
    int key;
} Node;

/* Insert a new node into a red black tree */
extern void tree_rb_insert(Node ** node, Node * parent, int key);
/* Returns 1 if the key exists into the red black tree */
extern int tree_rb_find(Node * node, int key);
/* Prints the struct for a red black tree */
extern void tree_rb_print(Node * node);
/* Liberate the memory allocated for a red black tree */
extern void tree_rb_free(Node * node);
