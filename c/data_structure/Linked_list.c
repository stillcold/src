#include "mystructures.h"

#include <stdio.h>
#include <stdlib.h>

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
LIST_NODE* initiateList(void)
{
    LIST_NODE *head = malloc(sizeof (LIST_NODE));

    if (!head)
        return NULL;

    head->element = 0;
    head->next = NULL;

    return head;
}


/* Build a sorted list */

boolean insertElement(LIST_NODE *head, elementtype element)
{
    LIST_NODE *new_node;
    LIST_NODE *pointer = head;
    u32 i;

    if (!head)
    {
        return FALSE;
    }

    new_node = malloc(sizeof (LIST_NODE));
    new_node->element = element;
    new_node->next = NULL;

    for (i =0; i < head->element; i++)
    {
        if (!pointer->next)
        {
            break;
        }
        else
        {
            if (pointer->next->element < element)
            {
                pointer = pointer->next;
            }
            else
            {
                break;
            }
        }
    }

    new_node->next = pointer->next;
    pointer->next = new_node;

    head->element++;

    return TRUE;
}


/* Traverse list and print element at the same time */

boolean printList(LIST_NODE *head)
{
    LIST_NODE *pointer = head;
    u32 i;

    if (!head)
    {
        return FALSE;
    }

    for (i = 0; i < head->element; i++)
    {
        pointer = pointer->next;
        printf("%u\t",pointer->element);
    }
    printf("\n");

    return TRUE;
}
