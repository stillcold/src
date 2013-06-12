#include "mystructures.h"

#include <stdlib.h>

RB_NODE Gbl_leaf = {.color = black};

static void rb_tree_insert_fixup (RB_TREE *tree, RB_NODE *node);

static void left_rotate (RB_TREE *tree, RB_NODE *node);

static void right_rotate (RB_TREE *tree, RB_NODE *node);


/**************************************************************************
 *
 * A simple implement of Red-Black-Tree.
 *
 * Copyright (c) 2013, Chao Guan <mr_kernel@163.com>
 * All rights reserved.
 *
 *************************************************************************/

RB_NODE* rb_node_create (void *element, RB_COLOR color)
{
    RB_NODE *newNode = calloc (1, sizeof (RB_NODE));


    newNode->element = element;
    newNode->color = color;
    newNode->left = newNode->right = &Gbl_leaf;

    return newNode;
}

RB_TREE* rb_tree_initialize (COMPARE_FUNCTION *compare)
{
    RB_TREE *newTree;


    newTree = calloc (1, sizeof (RB_TREE));
    newTree->root = &Gbl_leaf;
    newTree->compare = compare;

    return newTree;
}


/**************************************************************************
 *
 * As for the return value or return type, I have no idea yet. Maybe
 * return the new created node is a good chioce.
 *
 *************************************************************************/

void rb_tree_insert (RB_TREE *tree, void* element)
{
    /* The new created node will be the child of this node */
    RB_NODE *node_insert_to;
    /* Help to find the place to insert */
    RB_NODE *node_pilot;
    RB_NODE *node_new;


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
    RB_NODE *uncle = NULL;

    /* If the parent of it is red, then nothing need to do */

    while (node->parent->color == red)
    {
        /* If node's parent is a left child */

        if (node->parent == node->parent->parent->left)
        {
            uncle = node->parent->parent->right;

            /* Case 1 */

            if (uncle->color == red)
            {
                node->parent->color = black;
                node->parent->parent->color = black;
                uncle->color = red;

                /* Used for while, fix up will continue */

                node = node->parent->parent;
                if (!node->parent)
                {
                    break;
                }
            }
            else if (node == node->parent->right) /* Case 2 */
            {
                /* Just change Case 2 to Case 3 */

                node = node->parent;
                left_rotate (tree, node);

                /* Case 3 */
                node->parent->color = black;
                node->parent->parent->color = red;
                right_rotate (tree, node->parent->parent);
            }
        }
        else /* node's parent is a right child */
        {
            uncle = node->parent->parent->left;

            /* Case 1 */

            if (uncle->color == red)
            {
                node->parent->color = black;
                node->parent->parent->color = black;
                uncle->color = red;

                /* Used for while, fix up will continue */

                node = node->parent->parent;
            }
            else if (node == node->parent->right) /* Case 2 */
            {
                /* Just change Case 2 to Case 3 */

                node = node->parent;
                right_rotate (tree, node);

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
static void left_rotate (RB_TREE *tree, RB_NODE *node)
{
    RB_NODE *right_child = NULL;


    right_child = node->right;
    node->right = right_child->left;

    /* Modify the parent of left[right_child] if it is not nil node */

    if (right_child->left != &Gbl_leaf)
    {
        right_child->left->parent = node;
    }

    node->parent = right_child->parent;

    /* If the tree is an empty one before insert this node */

    if (node->parent == &Gbl_leaf)
    {
        tree->root = right_child;
    }

    /* If node is a left child */

    if (node == node->parent->left)
    {
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


static void right_rotate (RB_TREE *tree, RB_NODE *node)
{
    RB_NODE *left_child = NULL;


    left_child = node->left;
    node->left = left_child->right;

    /* Modify the parent of right[left_child] if it is not nil node */

    if (left_child->right != &Gbl_leaf)
    {
        left_child->right->parent = node;
    }

    node->parent = left_child->parent;

    /* If the tree is an empty one before insert this node */

    if (node->parent == &Gbl_leaf)
    {
        tree->root = left_child;
    }

    /* If node is a left child */

    if (node == node->parent->left)
    {
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
