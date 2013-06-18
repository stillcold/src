#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node             *next;
    struct node             *prev;
    int                     i;
    int                     j;
} NODE;

int main(void)
{
    NODE                    *p1;
    NODE                    *p2;
    int                     *p3;
    int                     *p4;
    char                    *p5;
    char                    *p6;
    int                     *p7;
    char                    *p8;
    char                    *p9;

    p1 = malloc (sizeof (NODE));
    p2 = malloc (sizeof (NODE));
    p3 = malloc (sizeof (int));
    p4 = malloc (sizeof (int));
    p5 = malloc (sizeof (char));
    p6 = malloc (sizeof (char));
    p7 = malloc (sizeof (int));
    p8 = malloc (sizeof (char));
    p9 = malloc (sizeof (char));

    printf(" %d %d %p %p %p %p %p %p %p %lu %lu\n", &p1,&p2, p3, p4, p5, p6,p7, p8, p9, sizeof(NODE), sizeof(int));

    return 1;

}
