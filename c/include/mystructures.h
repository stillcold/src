#include "mytypes.h"

#ifndef _MYSTRUCTRURE_H
#define _MYSTRUCTRURE_H
#endif

/* Node of a linked-list */

typedef struct node
{
    u32 element;
    struct node *next;
} node;


