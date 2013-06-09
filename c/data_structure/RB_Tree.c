#include "mystructures.h"

#include <stdlib.h>

RB_NODE Gbl_leaf = {.color = black};

static void rb_tree_insert_fixup (RB_TREE *tree, RB_NODE *node);


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

    /* If the parent of it is red, then nothing need to do */

    while (node->parent->color == red)
    {
        return;
    }

    /* While statement dosen't cover the color of the root */

    tree->root->color = black;
    return;
}
