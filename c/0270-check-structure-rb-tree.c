#include "mystructures.h"

#include <stdio.h>
#include <math.h>

#define MAX_NUM 100

int Gbl_element [MAX_NUM];
boolean Gbl_marked = FALSE;
u8 Gbl_level [MAX_NUM];
u32 Gbl_index;
u32 Gbl_color [MAX_NUM];
u32 Gbl_max_level;
u32 Gbl_max_width;

boolean compare_element (void *element_a, void *element_b);

static void print_level(RB_TREE *tree, u32 level);

static void print_tree(RB_TREE *tree);

static void traverse_and_get_level (RB_NODE* root, u32 level);

static void traverse_and_get_data (RB_NODE* root, u32 level);

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
    u32 j;
    boolean odd = TRUE;
    double node_number_of_level;
    u32 width_node;
    u32 offset_node;
    u8 offset_beginning;


    node_number_of_level = pow (2, (level - 1));
    width_node = Gbl_max_width / node_number_of_level;
    offset_node = width_node - 8;
    offset_beginning = offset_node / 2;
    for (i = 0; i < offset_beginning; i++ )
    {
        printf (" ");
    }

    for (i = 0; i < MAX_NUM; i++)
    {
        if (!Gbl_level[i])
        {
            printf ("\n");
            break;
        }

        if ((Gbl_level[i] == level) && (level != 1))
        {
            if (odd)
            {
                printf ("   /    ");
            }
            else
            {
                printf (" \\      ");
            }

            odd = odd ? FALSE : TRUE;

            for (j = 0; j < offset_node; j++)
            {
                printf (" ");
            }
        }
    }

    for (i = 0; i < offset_beginning; i++ )
    {
        printf (" ");
    }

    for (i = 0; i < MAX_NUM; i++)
    {
        if (!Gbl_level[i])
        {
            printf ("\n");
            break;
        }

        if (Gbl_level[i] == level)
        {
            if (Gbl_element[i])
            {
                printf ("  %-4d  ", Gbl_element[i]);
            }
            else
            {
                printf ("  NULL  ");
            }

            for (j = 0; j < offset_node; j++)
            {
                printf (" ");
            }
        }
    }

    for (i = 0; i < offset_beginning; i++ )
    {
        printf (" ");
    }

    for (i = 0; i < MAX_NUM; i++)
    {
        if (!Gbl_level[i])
        {
            printf ("\n");
            return;
        }

        if (Gbl_level[i] == level)
        {
            if (Gbl_color[i])
            {
                printf("  Black ");
            }
            else
            {
                printf("  Red   ");
            }

            for (j = 0; j < offset_node; j++)
            {
                printf (" ");
            }
        }
    }

    printf ("\n");
    return;
}

static void print_tree(RB_TREE *tree)
{
    u32 i;


    /* root will be level 1 */
    traverse_and_get_level (tree->root, 1);
    /*
     *
     * For example:
     *
     * If a tree has a level 5, its last level (5th level ) has only a nil
     * node, then, at its 1th level, it has 1 node, 2th has 4, thus, 4th
     * has 8. 
     *
     * And 8 = pow (2, 5-2)
     *
     */
    Gbl_max_width = 8 * pow (2, (Gbl_max_level - 2));
    printf ("print tree - Gbl_max_level %d\n", Gbl_max_level);
    traverse_and_get_data (tree->root, 1);
    for (i = 1; i < Gbl_max_level; i++)
    {
        print_level (tree, i);
    }

    return;
}

static void traverse_and_get_level (RB_NODE* root, u32 level)
{
    Gbl_max_level = (Gbl_max_level < level) ? level : Gbl_max_level;

    if (!root->element)
    {
        return;
    }

    if (root->left)
    {
        traverse_and_get_level (root->left, level+1);
    }

    if (root->right)
    {
        traverse_and_get_level (root->right, level+1);
    }

    return;
}


static void traverse_and_get_data (RB_NODE* root, u32 level)
{
    u32 i;
    u32 j;
    u32 counter = 1;
    u32 level_mark;


    if (!root->element)
    {
        level_mark = level;
        for (i = level; i < Gbl_max_level; i++)
        {
            for (j = 0; j < counter; j++)
            {
                Gbl_element[Gbl_index] = 0;
                Gbl_level[Gbl_index] = level_mark;
                Gbl_color[Gbl_index] = red;
                Gbl_index++;
            }
            level_mark++;
            counter *= 2;
        }

        return;
    }

    if (root->left)
    {
        traverse_and_get_data (root->left, level+1);
    }

    Gbl_element[Gbl_index] = *(int *)root->element;
    Gbl_level[Gbl_index] = level;
    Gbl_color[Gbl_index] = root->color;
    Gbl_index ++;

    if (root->right)
    {
        traverse_and_get_data (root->right, level+1);
    }

    return;
}

int main(void)
{
    RB_TREE *tree = rb_tree_initialize (compare_element);

    int a = 5;
    int b = 3;
    int c = 7;
    int d = 8;
    int e = 4;

    rb_tree_insert (tree, &a);
    rb_tree_insert (tree, &b);
    rb_tree_insert (tree, &c);
    rb_tree_insert (tree, &d);
    rb_tree_insert (tree, &e);
    print_tree (tree);

    return 1;
}
