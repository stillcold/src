/**************************************************************************                                                                              
 *                                                                                                                                                       
 * A simple implementation of quick_sort_.                                                                                                            
 *                                                                                                                                                       
 * Copyright (c) 2013, Chao Guan <mr_kernel@163.com>                                                                                                     
 * All rights reserved.                                                                                                                                  
 *                                                                                                                                                       
 *************************************************************************/
#include "myutilities.h"
#include <stdio.h>

static boolean qsort(
    COMPARE_FUNCTION*       compare,
    SWAP_FUNCTION*          swap,
    void*                   target,
    int                     low,
    int                     high
);

/*
 * Function: qsort
 * return:
 *     0: function works properly.
 *     none-0: function occurs an error.
 * parameters:
 *     target: name of the array.
 *     low: index of the first element, starts from 0.
 *     high: indext of the last elemnt, end at length-1.
 */
static boolean qsort(
    COMPARE_FUNCTION*       compare,
    SWAP_FUNCTION*          swap,
    void*                   target,
    int                     low,
    int                     high
){
    int                     offsetl = low;
    int                     offseth = high;

    boolean                 ret;

    if (offsetl > offseth){
        return FALSE;
    }

    if (offsetl == offseth){
        return TRUE;
    }

    while (offsetl < offseth){
        /* 
         * Have to find the first less-than-pivot element before 
         * the first larger-than-pivot element, then we will do a swap 
         * later.
         */

        while ((*compare) (target, offseth, low) && (offsetl < offseth))
        {
            offseth--;
        }
        while ((*compare) (target, low, offsetl) && (offsetl < offseth))
        {
            offsetl++;
        }

        /* Swap offsetl and offseth element */

/*
        printf ("%*d %*d\n", 3, *(target+offsetl), 3, *(target+offseth));
        temp = *(target+offsetl);
        *(target+offsetl) = *(target+offseth);
        *(target+offseth) = temp;
*/

        if (offsetl != offseth)
            swap (target, offsetl, offseth);

    }

    /* Put pivot to its right place */

    if (offsetl != low)
        swap(target, offsetl, low);

    if(low!=offsetl){
        ret = qsort(compare, swap, target, low, offsetl);
    }
    if(high!=offsetl+1){
        ret = qsort(compare, swap, target, offsetl+1, high);
    }

    return ret;
}

boolean sort(
    COMPARE_FUNCTION*       compare,
    SWAP_FUNCTION*          swap,
    void*                   target,
    int                     length
){
    return qsort(compare, swap, target, 0, length-1);
}
