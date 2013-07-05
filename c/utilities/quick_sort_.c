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

static boolean qsort(int*, int , int );

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
static boolean qsort(int* target, int low, int high){
    int offsetl = low;
    int offseth = high;

    int temp;
    int pivot = *(target+low);
    boolean                 ret;

    if (offsetl > offseth){
        return FALSE;
    }

    if (offsetl == offseth){
        return TRUE;
    }

    /*
     * An extra unecessary swap exists in this while:
     * When offsetl equals to offseth, there is no need to do the exchange.
     * and unfortunately, this will definitely happen.
     */
    while (offsetl < offseth){
        /* 
         * Have to find the first less-than-pivot element before 
         * the first larger-than-pivot element, then we will do a swap 
         * later.
         */

        while (*(target+offseth) >= pivot && offsetl < offseth) offseth--;
        while (*(target+offsetl) <= pivot && offsetl < offseth) offsetl++;

        /* Swap offsetl and offseth element */

        temp = *(target+offsetl);
        *(target+offsetl) = *(target+offseth);
        *(target+offseth) = temp;

/*        SWAP((*(target+offsetl)),(*(target+offseth)));*/
    }

    /* Put pivot to its right place */

    temp = *(target+offsetl);
    *(target+offsetl) = pivot;
    *(target+low) = temp;

/*    SWAP((*(target+offsetl)),(*(target+low)));*/
    if(low!=offsetl){
        ret = qsort(target, low, offsetl);
    }
    if(high!=offsetl+1){
        ret = qsort(target, offsetl+1, high);
    }

    return ret;
}

boolean sort(int* target, int length, ...){
    return qsort(target, 0, length-1);
}
