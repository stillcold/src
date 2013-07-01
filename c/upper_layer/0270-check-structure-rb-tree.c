#include "mystructures.h"

#include <stdio.h>


boolean compare_element (void *element_a, void *element_b)
{
    return (*(u32 *)element_a) > (*(u32 *)element_b) ? TRUE : FALSE;
}


int main(void)
{
    RB_TREE                 *tree;
    u32                     data[MAX_NUM];
    u32                     i;


    tree = rb_tree_initialize (compare_element);
    for (i = 0; i < MAX_NUM; i++)
    {
        printf ("Please input the value of each node, terminal with 0:\n");
        scanf("%u", &data[i]);
        if (!data[i])
            return 0;
        rb_tree_insert (tree, (data+i));
        print_tree (tree);
    }

    return 0;
}
