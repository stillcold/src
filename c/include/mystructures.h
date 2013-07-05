#ifndef _MYSTRUCTRURE_H
#define _MYSTRUCTRURE_H

#include "mytypes.h"

/* A RB_TREE can has no more than MAX_NUM nodes */
#define MAX_NUM             1000

/* Global variables */

extern u32                  Gbl_element [MAX_NUM];
extern boolean              Gbl_marked;
extern u8                   Gbl_level [MAX_NUM];
extern u32                  Gbl_index;
extern u8                   Gbl_color [MAX_NUM];
extern u32                  Gbl_max_level;
extern u32                  Gbl_max_width;

typedef u32                 elementtype;

/* Node of a linked-list */

typedef struct node
{
    u32                     element;
    struct node             *next;
} LIST_NODE;


LIST_NODE* initiateList(void);

boolean insertElement(LIST_NODE *head, elementtype element);

boolean printList(LIST_NODE *head);


/**************************************************************************
 *
 * A Red-Black-Tree structure will be implemented below.
 *
 *************************************************************************/

typedef enum red_black_color
{
    red,
    black
} RB_COLOR;

typedef struct red_black_node
{
    void*                   element;    /* Anything could be its element */
    RB_COLOR                color;
    struct red_black_node   *left;      /* Point to left child */
    struct red_black_node   *right;     /* Point to right child */
    struct red_black_node   *parent;    /* Point to parent */
} RB_NODE;


/*
 *
 * NOT sure if this will make the code UNreadble.
 *
 */

typedef boolean (COMPARE_FUNCTION) (void *element_a, void *element_b);

typedef struct red_black_tree
{
    RB_NODE                 *root;
    COMPARE_FUNCTION        *compare;
} RB_TREE;

RB_NODE* rb_node_create (void *element, RB_COLOR color);

RB_TREE* rb_tree_initialize (COMPARE_FUNCTION *compare);

void rb_tree_insert (RB_TREE *tree, void* element);

void left_rotate (RB_TREE *tree, RB_NODE *node);

void right_rotate (RB_TREE *tree, RB_NODE *node);

void print_tree(RB_TREE *tree);

/*
 *
 * One have to implement this function to use all the intefaces.
 *
 */
boolean compare_element (void *element_a, void *element_b);

#endif
