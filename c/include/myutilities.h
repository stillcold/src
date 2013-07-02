#ifndef _MYUTILITIES_H
#define _MYUTILITIES_H

#include "mytypes.h"

#define MAX_PATTERN_LENGTH  100

extern s32                  next[MAX_PATTERN_LENGTH];

/*
 * Greatest common divisor
 */
u32 gcd (u32 num_A, u32 num_B);

/*
 * get next for KMP_matcher
 */
void get_next (char pattern[]);

/*
 * KMP
 */
s32 KMP_matcher (char text[], char pattern[]);

#endif
