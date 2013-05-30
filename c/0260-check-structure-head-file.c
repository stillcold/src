#include <stdio.h>
#include <malloc.h>

#include "mystructures.h"

/* Traverse list and print element at the same time */
boolean printList(node *head);

int main(void)
{
    node *head = NULL;
    head = initiateList();
    if (!head)
    {
        printf("Shit, still empty.\n");
    }
    insertElement(head, 2);
    insertElement(head, 1);
    insertElement(head, 5);
    insertElement(head, 4);
    insertElement(head, 3);
    printList(head);
    return 0;
}

node* initiateList(void)
{
    node *head = malloc(sizeof (node));

    if (!head)
        return NULL;

    head->element = 0;
    head->next = NULL;

    return head;
}

boolean insertElement(node *head, elementtype element)
{
    node *new_node;
    node *pointer = head;
    u32 i;

    if (!head)
    {
        return FALSE;
    }

    new_node = malloc(sizeof (node));
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

boolean printList(node *head)
{
    node *pointer = head;
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
