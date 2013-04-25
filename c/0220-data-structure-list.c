#include <stdio.h>
#include <malloc.h>

typedef struct list{
    List *next;
    int node;
} List;

int main(void)
{
    List l;
    l.node = 1;

    l.next = (List *) malloc(sizeof(List));
    l.next.node =2;

    printf("%d %d\n",l.node, l.next.node);
    return 0;
}
