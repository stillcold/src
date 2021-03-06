#ifndef _MYALGORITHM_H
#define _MYALGORITHM_H

#include "myconfig.h"
#include "mytypes.h"
#include "mystatus.h"
#include "mymacros.h"

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
 * Ut_heap_sort.c
 *
 *************************************************************************/


#define HEAP_MAX_SIZE       101
#define HEAP_MAX_LENGTH     100

void heap_sort(int length);

void print_heap(int length);


/**************************************************************************
 *
 * agbitmap.c
 *
 *************************************************************************/

#define MAP_MAX_LENGTH      10000

void set_bit_in_map(u32 index);

void reset_bit_in_map(u32 index);

boolean check_bit_in_map(u32 index);

#ifdef DEBUG_MODE

void show_bitmap(void);

#endif


/**************************************************************************
 *
 * agbitmap.c
 *
 *************************************************************************/

int dp_demo(int depth);

void init_dp_array(void);


/**************************************************************************
 *
 * ag_Artificial_Neural_Network.c
 *
 *************************************************************************/

/* Program will be terminated when difference smaller than this value*/
#define TARGET_ERROR_VALUE  0.0009
#define MAX_LOOP_TIMES      10000000

STATUS initiate_neural_network(void);
STATUS train_neural_network(void);
STATUS get_delta(void);
STATUS modify_network_weight(void);
double proceed(double fan_in);
double new_rate(double original_rate, double guard);
double incentive_function(double fan_in);
double get_differential_coefficient(double fan_in);

/**************************************************************************
 *
 * ag_manacher.c
 *
 *************************************************************************/

int manacher_length;

char original_manacher_str[ONE_THOUSAND];
int manacher_result[ONE_THOUSAND];

void init_manacher(void);
void manacher_do(void);

#endif
