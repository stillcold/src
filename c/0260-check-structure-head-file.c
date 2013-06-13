#include <stdio.h>
#include <malloc.h>

#include "mystructures.h"


int main(void)
{
    LIST_NODE *head = NULL;
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


