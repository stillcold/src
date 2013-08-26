#include "mystructures.h"
#include "mytypes.h"

#include <string.h>

#define                     ELEMENT_NUMBER 1000

u32                         number[ELEMENT_NUMBER];
u32                         parent[ELEMENT_NUMBER];
u32                         weight[ELEMENT_NUMBER]; /* Rank */
s8                          exist[ELEMENT_NUMBER];


/**************************************************************************
 *
 * Make set./ Initialize the whole set, I put memset here to save time.
 *
 *************************************************************************/

void UF_set_init(void){
    memset(weight, 0, sizeof (weight));
    memset(exist, 0xff, sizeof (exist));

    return;
}


/**************************************************************************
 *
 * Create each element of the set.
 *
 *************************************************************************/

void UF_set_create(u32 element){
    if (exist[element] == 1)
        return;

    number[element] = 1;
    parent[element] = element;
    exist[element] = 1;

    return;
}


/**************************************************************************
 *
 * Find parent.
 *
 *************************************************************************/

u32 UF_set_find(u32 element){
    u32                     temp = element;

    while (parent[temp] != temp){
        temp = parent[temp];
    }

    parent[element] = temp;

    return temp;
}


/**************************************************************************
 *
 * Get the number of element in a single set group.
 *
 *************************************************************************/

u32 UF_set_get_number(u32 element){
    element = UF_set_find(element);

    return number[element];
}

/**************************************************************************
 *
 * Set union.
 *
 *************************************************************************/

void UF_set_union(u32 element_A, u32 element_B){
    element_A = UF_set_find(element_A);
    element_B = UF_set_find(element_B);

    if (element_A == element_B){
        return;
    }

    if (weight[element_A] < weight[element_B]){
        parent[element_A] = element_B;
        number[element_B] += number[element_A];
    } else {
        parent[element_B] = element_A;
        number[element_A] += number[element_B];

        if (weight[element_A] == weight[element_B]){
            weight[element_A]++;
        }
    }
    return;
}
