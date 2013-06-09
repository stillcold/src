#ifndef _MYSTRUCTRURE_H
#define _MYSTRUCTRURE_H

#include "mytypes.h"

typedef u32 elementtype;

/* Node of a linked-list */

typedef struct node
{
    u32 element;
    struct node *next;
} node;

/*
 * Implementation of the funcstions below can be found in 0260
 *
 * Watch out this wrong usage:
 *
 *     boolean initiateList(node *head){node *new_node = ...; head = new_node}
 *
 *     then we invoke it like this:
 *
 *         initiateList(head) 
 *
 *     it can't initiate the head, because the head is in fact not changed by
 *     the function. Most function can only chang *head, can't change head 
 *     itself. But initiateList(head) try to change head itself, it can't work.
 */
node* initiateList(void);

/* Build a sorted list */
boolean insertElement(node *head, elementtype element);


/**************************************************************************
 *
 * A Red-Black-Tree structure will be implemented here.
 *
 *************************************************************************/

typedef enum red_black_color
{
    red,
    black
} RB_COLOR;

typedef struct red_black_node
{
    void* element;                      /* Anything could be its element */
    RB_COLOR color;
    struct red_black_node *left;         /* Point to left child */
    struct red_black_node *right;        /* Point to right child */
    struct red_black_node *parent;       /* Point to parent */
} RB_NODE;

/**************************************************************************
 *
 * NOT sure if this will make the code UNreadble.
 *
 *************************************************************************/

typedef boolean (COMPARE_FUNCTION) (void *element_a, void *element_b);

typedef struct red_black_tree
{
    RB_NODE *root;
    COMPARE_FUNCTION *compare;
} RB_TREE;

RB_NODE* rb_node_create (void *element, RB_COLOR color);

RB_TREE* rb_tree_initialize (COMPARE_FUNCTION *compare);

void rb_tree_insert (RB_TREE *tree, void* element);

#endif
