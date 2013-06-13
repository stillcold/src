/**************************************************************************
 *
 * A simple implement of Red-Black-Tree.
 *
 * Copyright (c) 2013, Chao Guan <mr_kernel@163.com>
 * All rights reserved.
 *
 *************************************************************************/
#include "mystructures.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

u32                         Gbl_element [MAX_NUM];
boolean                     Gbl_marked;
u8                          Gbl_level [MAX_NUM];
u32                         Gbl_index;
u8                          Gbl_color [MAX_NUM];
u32                         Gbl_max_level;
u32                         Gbl_max_width;

RB_NODE Gbl_leaf = {.color = black};

static void rb_tree_insert_fixup (RB_TREE *tree, RB_NODE *node);

static void print_level(RB_TREE *tree, u32 level);

static void traverse_and_get_level (RB_NODE* root, u32 level);

static void traverse_and_get_data (RB_NODE* root, u32 level);

static void clear_data (void);



RB_NODE* rb_node_create (void *element, RB_COLOR color)
{
    RB_NODE                 *newNode;


    newNode = calloc (1, sizeof (RB_NODE));
    if (!newNode)
    {
        fprintf (stderr, "Function: rb_node_create- no memory\n");
        return NULL;
    }
    newNode->element = element;
    newNode->color = color;
    newNode->left = newNode->right = &Gbl_leaf;
    newNode->parent = NULL;

    return newNode;
}

RB_TREE* rb_tree_initialize (COMPARE_FUNCTION *compare)
{
    RB_TREE                 *newTree;


    newTree = calloc (1, sizeof (RB_TREE));
    if (!newTree)
    {
        fprintf (stderr, "Function: rb_tree_initialize- no memory\n");
        return NULL;
    }
    newTree->root = &Gbl_leaf;
    newTree->compare = compare;

    return newTree;
}


/**************************************************************************
 *
 * As for the return value or return type, I have no idea yet. Maybe
 * return the new created node is a better chioce.
 *
 *************************************************************************/

void rb_tree_insert (RB_TREE *tree, void* element)
{
    /* The new created node will be the child of this node */
    RB_NODE                 *node_insert_to;
    /* Help to find the place to insert */
    RB_NODE                *node_pilot;
    RB_NODE                *node_new;


    node_insert_to = node_pilot = tree->root;
    
    /* Find the place for the new node */

    while (node_pilot != &Gbl_leaf)
    {
        node_insert_to = node_pilot;
        if ((*(tree->compare)) (node_pilot->element, element))
        {
            node_pilot = node_pilot->left;
        }
        else
        {
            node_pilot = node_pilot->right;
        }
    }

    /* Empty tree, just set new node as root */

    if (node_insert_to == &Gbl_leaf)
    {
        node_new = rb_node_create (element, black);
        tree->root = node_new;
        return;
    }

    /* Insert the new node, then adjust it */

    node_new = rb_node_create(element, red);
    if ((*(tree->compare)) (node_insert_to->element, element))
    {
        node_insert_to->left = node_new;
    }
    else
    {
        node_insert_to->right = node_new;
    }

    node_new->parent = node_insert_to;
    rb_tree_insert_fixup (tree, node_new);
    return;
}


/**************************************************************************
 *
 * Actually, this is a recursion 
 *
 *************************************************************************/

static void rb_tree_insert_fixup (RB_TREE *tree, RB_NODE *node)
{
    RB_NODE                 *uncle = NULL;


    /* If the parent of it is red, then nothing need to do */

    while (node->parent->color == red)
    {
        /* If node's parent is a left child */

        if (node->parent == node->parent->parent->left)
        {
            uncle = node->parent->parent->right;

            /* Case 1 */

            if ((uncle != &Gbl_leaf) && (uncle->color == red))
            {
                node->parent->color = black;
                node->parent->parent->color = red;
                uncle->color = black;

                /* Used for while, fix up will continue */

                node = node->parent->parent;
                if (!node->parent)
                {
                    break;
                }
            }
            else 
            {
                if (node == node->parent->right) /* Case 2 */
                {
                    /* Just change Case 2 to Case 3 */

                    node = node->parent;
                    left_rotate (tree, node);
                }

                /* Case 3 */
                node->parent->color = black;
                node->parent->parent->color = red;
                right_rotate (tree, node->parent->parent);
            }
        }
        else /* node's parent is a right child */
        {
            uncle = node->parent->parent->left;

            /* Case 1, note: leaf is red */

            if ((uncle != &Gbl_leaf) && (uncle->color == red))
            {
                node->parent->color = black;
                node->parent->parent->color = red;
                uncle->color = black;

                /* Used for while, fix up will continue */

                node = node->parent->parent;
                if (!node->parent)
                {
                    break;
                }
            }
            else /* uncle is black or nil */
            {
                if (node == node->parent->left) /* Case 2 */
                {
                    /* Just change Case 2 to Case 3 */

                    node = node->parent;
                    right_rotate (tree, node);
                }

                /* Case 3 */
                node->parent->color = black;
                node->parent->parent->color = red;
                left_rotate (tree, node->parent->parent);
            }
        }
    }

    /* While statement dosen't cover the color of the root */

    tree->root->color = black;
    return;
}


/**************************************************************************
 *
 * For example:
 *
 * We want to left rotate (tree, x), just change right child of a node to
 * its parent, and do the rest needded changes:
 *
 *               parent[x]              parent[x]
 *                  \                      \
 *                   x          ---->      right_child[x]
 *                    \                      /
 *                     right_child[x]       x
 *
 *************************************************************************/

void left_rotate (RB_TREE *tree, RB_NODE *node)
{
    RB_NODE                 *right_child = NULL;


    right_child = node->right;
    if (right_child == &Gbl_leaf)
    {
        fprintf (stderr, "Function: right_rotate- invalid right child\n");
        return;
    }
    node->right = right_child->left;

    /* Modify the parent of left[right_child] if it is not nil node */

    if (right_child->left != &Gbl_leaf)
    {
        right_child->left->parent = node;
    }

    right_child->parent = node->parent;

    /* If the tree is an empty one before insert this node */

    if (node->parent == &Gbl_leaf)
    {
        tree->root = right_child;
    }


    if (node == tree->root)
    {
        /* Node is root */

        tree->root = right_child;
    }
    else if (node == node->parent->left)
    {
        /* Node is a left child */

        node->parent->left = right_child;
    }
    else /* Node is a right child */
    {
        node->parent->right = right_child;
    }

    right_child->left = node;
    node->parent = right_child;
    return;
}


void right_rotate (RB_TREE *tree, RB_NODE *node)
{
    RB_NODE                 *left_child = NULL;


    left_child = node->left;
    if (left_child == &Gbl_leaf)
    {
        fprintf (stderr, "Function: right_rotate- invalid left child\n");
        return;
    }
    node->left = left_child->right;

    /* Modify the parent of right[left_child] if it is not nil node */

    if (left_child->right != &Gbl_leaf)
    {
        printf ("leaf- %p target- %p\n",&Gbl_leaf, left_child->right);
        left_child->right->parent = node;
    }

    left_child->parent = node->parent;

    /* If the tree is an empty one before insert this node */

    if (node->parent == &Gbl_leaf)
    {
        tree->root = left_child;
    }

    
    if (tree->root == node)
    {
        /* Node is the root */

        tree->root = left_child;
    }
    else if (node == node->parent->left)
    {
        /* Node is a left child */

        node->parent->left = left_child;
    }
    else /* Node is a right child */
    {
        node->parent->right = left_child;
    }

    left_child->right = node;
    node->parent = left_child;
    return;
}


/**************************************************************************
 *
 * This is a very stupid way to print the tree.
 * Unprinted part are all NIL node of the tree.
 *
 **************************************************************************/

void print_tree(RB_TREE *tree)
{
    u32 i;


    /* root will be level 1, then */

    traverse_and_get_level (tree->root, 1);
    /*
     *
     * For example:
     *
     * If a tree has a level 5, its last level (5th level ) has only a nil
     * node, then, at its 1th level, it has 1 node, 2th has 4, thus, 4th
     * has 8. 
     *
     * And 8 = pow (2, 5-2), that is why we have Gbl_max_level - 2 below.
     *
     */
    Gbl_max_width = 8 * pow (2, (Gbl_max_level - 2));
    printf ("print tree - Gbl_max_level %d\n", Gbl_max_level);
    clear_data ();
    traverse_and_get_data (tree->root, 1);
    for (i = 1; i < Gbl_max_level; i++)
    {
        print_level (tree, i);
    }

    printf ("\n");
    return;
}


/**************************************************************************
 *
 * Here is the logic:
 *
 * If we have 5 levels, then the last level will be all NIL node, the
 * second last level will have pow(2, 5-2) = 8 nodes, i.e:
 *
 *      pow (2, (Gbl_max_level - 2))
 *
 * Each node in last second level has 8 spaces, so the width in total is:
 *
 *      Gbl_max_width = pow (2, (Gbl_max_level - 2)) * 8
 *
 * For each level, the number of the nodes will be:
 *
 *      node_number_of_level = pow (2, (level - 1))
 *
 * In average, the width for each node will be:
 *
 *      width_node = Gbl_max_width / node_number_of_level
 *
 * As we know, each node will take 8 spaces while print it(generally, we
 * use this format: printf ("  %-4u  ")). So the offset besides the spaces
 * taken by itself will be:
 *
 *      offset_node = width_node - 8
 *
 * And every node will be put in the middle of its place, so, offset in
 * the beginning of each line will be:
 *
 *      offset_beginning = offset_node / 2
 *
 *
 *************************************************************************/

static void print_level(RB_TREE *tree, u32 level)
{
    u32                     i;
    u32                     j;
    boolean                 odd = TRUE;
    double                  node_number_of_level;
    u32                     width_node;
    u32                     offset_node;
    u8                      offset_beginning;


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
            if (Gbl_color[i] != 2)
            {
                if (odd)
                {
                    printf ("   /    ");
                }
                else
                {
                    printf (" \\      ");
                }

            }
            else
            {
                printf ("        ");
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
                printf ("  %-4u  ", Gbl_element[i]);
            }
            else
            {
                printf ("        ");
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
            if (Gbl_color[i] == black)
            {
                printf("  Black ");
            }
            else if (!Gbl_color[i])
            {
                printf("  Red   ");
            }
            else
            {
                printf("        ");
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
    u32                     i;
    u32                     j;
    u32                     counter = 1;
    u32                     level_mark;


    if (!root->element)
    {
        level_mark = level;
        for (i = level; i < Gbl_max_level; i++)
        {
            for (j = 0; j < counter; j++)
            {
                Gbl_element[Gbl_index] = 0;
                Gbl_level[Gbl_index] = level_mark;
                /*
                 * Note:
                 *
                 * We only defined 2 colors - red and black, so red == 0
                 * and black == 1, that means the value "2" here is 
                 * actually invalid.
                 */
                Gbl_color[Gbl_index] = 2;
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

    Gbl_element[Gbl_index] = *(u32 *)root->element;
    Gbl_level[Gbl_index] = level;
    Gbl_color[Gbl_index] = root->color;
    Gbl_index ++;

    if (root->right)
    {
        traverse_and_get_data (root->right, level+1);
    }

    return;
}

static void clear_data (void)
{
    u32                     i;


    for (i = 0; i < MAX_NUM; i++)
    {
        Gbl_element[i] = 0;
        Gbl_level[i] = 0;
        Gbl_color[i] = 0;
    }

    Gbl_index = 0;
    return;
}
