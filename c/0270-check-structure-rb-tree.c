#include "mystructures.h"

#include <stdio.h>

#define MAX_NUM 100

int Gbl_element [MAX_NUM];
boolean Gbl_marked = FALSE;
u8 Gbl_level [MAX_NUM];
u32 Gbl_index;
u32 Gbl_color [MAX_NUM];
u32 Gbl_max_level;

boolean compare_element (void *element_a, void *element_b);

static void print_level(RB_TREE *tree, u32 level);

static void print_tree(RB_TREE *tree);

static void traverse_and_mark_tree (RB_NODE* root, u32 level);

boolean compare_element (void *element_a, void *element_b)
{
    return (*(int *)element_a) > (*(int *)element_b) ? TRUE : FALSE;
}

/**************************************************************************
 *
 * This is a very stupid way to print the tree.
 *
 **************************************************************************/

static void print_level(RB_TREE *tree, u32 level)
{
    u32 i;


    if (!Gbl_marked)
    {
        traverse_and_mark_tree (tree->root, 1);
        Gbl_marked = TRUE;
    }

    printf ("\n");
    for (i = 0; i < (Gbl_max_level - level); i++ )
    {
        printf ("    ");
    }

    for (i = 0; i < MAX_NUM; i++)
    {
        if (!Gbl_level[i])
        {
            return;
        }

        if (Gbl_level[i] && Gbl_level[i] < level)
        {
            continue;
        }
        
        if (Gbl_color[i])
        {
            printf("Black   ");
        }
        else
        {
            printf("Red     ");
        }
    }

    for (i = 0; i < (Gbl_max_level - level); i++ )
    {
        printf ("\n    ");
    }

    for (i = 0; i < MAX_NUM; i++)
    {
        if (!Gbl_level[i])
        {
            return;
        }

        if (Gbl_level[i] && Gbl_level[i] < level)
        {
            continue;
        }
        
        printf("%d\t", Gbl_element[i]);
    }

    return;
}

static void print_tree(RB_TREE *tree)
{
    RB_NODE* node;
    u32 i;


    node = tree->root;
    while (node)
    {
        Gbl_max_level ++;
        node = node->left;
    }

    for (i = 1; i < Gbl_max_level; i++)
    {
        print_level (tree, i);
    }

    return;
}

static void traverse_and_mark_tree (RB_NODE* root, u32 level)
{
    if (!root->element)
    {
        return;
    }

    if (root->left)
    {
        traverse_and_mark_tree (root->left, level+1);
    }

    Gbl_element[Gbl_index] = *(int *)root->element;
    Gbl_level[Gbl_index] = level;
    Gbl_color[Gbl_index] = root->color;
    Gbl_index ++;

    if (root->right)
    {
        traverse_and_mark_tree (root->right, level+1);
    }

    return;
}

int main(void)
{
    RB_TREE *tree = rb_tree_initialize (compare_element);

    int a = 1;
    int b = 2;
    int c = 8;
    int d = 4;
    int e = 5;

    rb_tree_insert (tree, &a);
    rb_tree_insert (tree, &b);
    rb_tree_insert (tree, &c);
    rb_tree_insert (tree, &d);
    rb_tree_insert (tree, &e);
    print_tree (tree);

    return 1;
}
