#ifndef _MYUTILITIES_H
#define _MYUTILITIES_H

#include "mytypes.h"

#define MAX_PATTERN_LENGTH  100

typedef boolean (COMPARE_FUNCTION) (void *target, int offset_1, int offset_2);

typedef void (SWAP_FUNCTION) (void *target, int offset_1, int offset_2);

/**************************************************************************
 *
 * Note:
 *      This SWAP can't swap two same variables' value
 *
 * For example: SWAP(a,a)
 *      ===result===>
 *      a=0
 *
 *************************************************************************/
#define SWAP(a,b)           {\
    a ^= b;\
    b ^= a;\
    a ^= b;\
}

extern s32                  next[MAX_PATTERN_LENGTH];


/**************************************************************************
 *
 * Greatest common divisor
 *
 *************************************************************************/

u32
gcd (
    u32                     num_A,
    u32                     num_B
);


/**************************************************************************
 *
 * get next value of a pattern for KMP_matcher
 *
 *************************************************************************/

void
get_next (
    char                    pattern[]
);


/**************************************************************************
 *
 * KMP
 *
 *************************************************************************/

s32
KMP_matcher (
    char                    text[],
    char                    pattern[]
);


/**************************************************************************
 *
 * sort, which will invoke quick_sort.
 *
 *************************************************************************/

boolean
sort (
    COMPARE_FUNCTION*       compare_function,
    SWAP_FUNCTION*          swap_function,
    void*                   target,
    int                     length
);

#endif
