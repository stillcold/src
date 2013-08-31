#ifndef _MYALGORITHM_H
#define _MYALGORITHM_H

#include "mytypes.h"

#define MAX_PATTERN_LENGTH  100

typedef boolean (COMPARE_FUNCTION) (void *target, int offset_1, int offset_2);

typedef void (SWAP_FUNCTION) (void *target, int offset_1, int offset_2);

typedef struct date_and_time {
    u16                     year;
    u8                      month;
    u8                      date;
    u8                      week;
    u8                      hour;
    u8                      minute;
    u8                      second;
} DATE_AND_TIME; 

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


/**************************************************************************
 *
 * bit_operation.c
 *
 * DESCRIPTION: Get the corresponding data type width in a certain platform
 *
 *************************************************************************/

int get_max_int_bit(void); /* Always 32 */
int get_max_long_bit(void); /* Always 32 or 64 */
int get_max_long_long_bit(void); /* Always 64 */


/**************************************************************************
 *
 * bit_operation.c
 *
 * DESCRIPTION: Set the Nth bit of a unsigned int to 1
 *
 *************************************************************************/

void set_bit(unsigned *address, int n);


/**************************************************************************
 *
 * bit_operation.c
 *
 * PARAMETERS: Va_args should be int.
 *
 * DESCRIPTION: Set muti-bit of a unsigned int to 1.
 *              Use it in this way:
 *                  set_bits(&number, 1, 2, 3)
 *
 *************************************************************************/

void set_bits(unsigned *address, ...);


/**************************************************************************
 *
 * bit_operation.c
 *
 * PARAMETERS:  p -> place/index, count from right
 *              n -> length, count from left
 *
 * DESCRIPTION: Get the last n bits of x from index p.
 *              Use it in this way:
 *                  get_bits(0000 0111, 3, 3) -> 111
 *                  get_bits(0001 1111, 5, 5) -> 11111
 *
 *************************************************************************/

unsigned get_bits(unsigned x, int p, int n);


/**************************************************************************
 *
 * bit_operation.c
 * Get number of ones of a bit-format number.
 * 7 -> 3
 * 8 -> 1
 *
 *************************************************************************/

int count_ones(int number);


/**************************************************************************
 *
 * time_and_date.c
 *
 * DESCRIPTION:
 *              Use it in this way:
 *                  get_day_of_year(.year = 2013, .month = 1, .day = 3)
 *                          -> 3
 *
 *************************************************************************/

u16 get_day_of_year(DATE_AND_TIME date_and_time);


/**************************************************************************
 *
 * time_and_date.c
 *
 *************************************************************************/

boolean is_leap_year(u16 year);


/**************************************************************************
 *
 * time_and_date.c
 *
 *************************************************************************/

char *get_month_name(DATE_AND_TIME date_and_time);

/**************************************************************************
 *
 * Ut_heap_sort.c
 *
 *************************************************************************/

#define HEAP_MAX_LENGTH    100

void heap_sort(int length);

#endif
