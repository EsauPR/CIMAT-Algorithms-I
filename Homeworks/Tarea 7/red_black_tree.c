/**
    ANSI C standard: c11
    balc_red_tree.c
    Purpose: Black-Red Tree module

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "red_black_tree.h"

#define __T_NODE_BLACK 0
#define __T_NODE_RED 1
#define __CHANGE_COLOR 1
#define __NOT_CHANGE_COLOR 0


/* Returns the parent of a node if this exists */
static Node * get_parent(Node * node) {
    return (node)? node->parent: NULL;
}

/* Returns the uncle of a node if this exists */
static Node * get_uncle(Node * parent, Node * grand_parent) {
    return (grand_parent)? (grand_parent->left != parent)? grand_parent->left : grand_parent->right  : NULL;
}

/* Left rotation */
static void left_rotation(Node * node, int change_color) {
    Node * parent = get_parent(node);
    Node * grand_parent = get_parent(parent);

    node->parent = grand_parent;
    if (grand_parent) {
        if (grand_parent->left == parent) {
            grand_parent->left = node;
        } else {
            grand_parent->right = node;
        }
    }

    parent->parent = node;
    parent->right = node->left;
    if (node->left) {
        node->left->parent = parent;
    }
    node->left = parent;

    if (change_color) {
        node->color = __T_NODE_BLACK;
        parent->color = __T_NODE_RED;
    }
}

/* Right rotation */
static void right_rotation(Node * node, int change_color) {
    Node * parent = get_parent(node);
    Node * grand_parent = get_parent(parent);

    node->parent = grand_parent;
    if (grand_parent) {
        if (grand_parent->left == parent) {
            grand_parent->left = node;
        } else {
            grand_parent->right = node;
        }
    }

    parent->parent = node;
    parent->left = node->right;
    if (node->right) {
        node->right->parent = parent;
    }
    node->right = parent;

    if (change_color) {
        node->color = __T_NODE_BLACK;
        parent->color = __T_NODE_RED;
    }
}

static void verify_rules(Node ** root, Node * node) {

    Node * parent = get_parent(node);
    Node * grand_parent = get_parent(parent);
    Node * uncle = get_uncle(parent, grand_parent);

    // The node is root or the parent is black
    if (parent == NULL || parent->color == __T_NODE_BLACK) {
        return;
    }

    // The uncle and parent are red => Change colors
    if (uncle && uncle->color == __T_NODE_RED) {
        uncle->color = !uncle->color;
        parent->color = !parent->color;
        grand_parent->color = (grand_parent->parent)? !grand_parent->color : grand_parent->color;
        verify_rules(root, grand_parent);
        return;
    }

    // Right rotation
    if (grand_parent->left == parent && parent->left == node) {
        right_rotation(parent, __CHANGE_COLOR);
    }
    // Left rotation
    else if (grand_parent->right == parent && parent->right == node) {
        left_rotation(parent, __CHANGE_COLOR);
    }
    // Left-Right rotation
    else if (grand_parent->left == parent && parent->right == node) {
        left_rotation(node, __NOT_CHANGE_COLOR);
        right_rotation(node, __CHANGE_COLOR);
    }
    // Right-Left rotation
    else if (grand_parent->right == parent && parent->left == node) {
        right_rotation(node, __NOT_CHANGE_COLOR);
        left_rotation(node, __CHANGE_COLOR);
    }

    // Update the root if the any rotation cause a new root
    if (parent && parent->parent == NULL) {
        *root = parent;
    } else if (node->parent == NULL) {
        *root = node;
    }
}

/* Insert a new node into a red black tree */
void tree_rb_insert(Node ** root, Node * parent, int key) {
    Node ** node = root;

    while(*node != NULL) {
        parent = *node;
        if ((*node)->key > key) { // Insert to the left
            node = &(*node)->left;
        } else { // Insert to the right
            node = &(*node)->right;
        }
    }

    *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        perror("tree_rb_insert()");
        return;
    }

    (*node)->key = key;
    (*node)->parent = parent;
    (*node)->left = (*node)->right = NULL;
    (*node)->color = (parent == NULL)? __T_NODE_BLACK: __T_NODE_RED;

    verify_rules(root, *node);
}

/* Returns 1 if the key exists into the red black tree */
int tree_rb_find(Node * root, int key) {
    if (root == NULL) {
        return 0;
    }

    if (root->key == key) {
        return 1;
    }

    if (root->key > key) {
        return tree_rb_find(root->left, key);
    }

    return tree_rb_find(root->right, key);
}

/* Prints the struct for a red black tree */
void tree_rb_print(Node * node) {
    if (node == NULL) {
        return;
    }

    tree_rb_print(node->left);

    if (node->parent) {
        printf("Node: %d, Color: %d, Parent: %d,", node->key, node->color, node->parent->key);
    } else {
        printf("Node: %d, Color: %d, Parent: %d,", node->key, node->color, node->key);
    }
    if (node->left) {
        printf(" Left: %d,", node->left->key);
    } else {
        printf(" Left: NULL,");
    }
    if (node->right) {
        printf(" Rigth: %d", node->right->key);
    } else {
        printf(" Rigth: NULL");
    }
    puts("");

    tree_rb_print(node->right);
}

/* Liberate the memory allocated for a red black tree */
void tree_rb_free(Node * node) {
    if (node == NULL) {
        return;
    }

    tree_rb_free(node->left);
    tree_rb_free(node->right);
    free(node);
}
