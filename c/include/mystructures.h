#include "mytypes.h"

#ifndef _MYSTRUCTRURE_H
#define _MYSTRUCTRURE_H
#endif

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
