#include "myalgorithm.h"
#include "mytypes.h"

#define BITSOFU32           32
#define MASK                0x1f/* 0001 1111*/
#define WIDTH               5

/**************************************************************************
 *
 * It is better to set this map structure as static.
 *
 *************************************************************************/

static u32                  map[1 + MAP_MAX_LENGTH >> WIDTH];

/**************************************************************************
 *
 * This is different from setbit or setbits in bit op.
 *
 * index / 32 (devide op) -> index >> WIDTH
 * index % 32 (mode op) -> index & MASK
 *
 *************************************************************************/

void set_bit_in_map(int index){
    map[index >> WIDTH] |= 1 << (index & MASK);
}

void reset_bit_in_map(int index){
    map[index >> WIDTH] &= ~(1 << (index & MASK));
}

boolean check_bit_in_map(int index){
    return (map[index >> WIDTH] & (1 << (index & MASK))) ? TURE : FALSE;
}
