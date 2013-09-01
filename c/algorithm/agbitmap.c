#include "myalgorithm.h"
#include "mytypes.h"
#ifdef DEBUG_MODE
#include <stdio.h>
#endif

#define BITSOFU32           32
#define MASK                0x1f/* 0001 1111*/
#define WIDTH               5

/**************************************************************************
 *
 * It is better to set this map structure as static.
 *
 *************************************************************************/

static u32                  map[1 + (MAP_MAX_LENGTH >> WIDTH)];

/**************************************************************************
 *
 * This is different from setbit or setbits in bit op.
 *
 * index / 32 (devide op) -> index >> WIDTH
 * index % 32 (mode op) -> index & MASK
 *
 *************************************************************************/

void set_bit_in_map(u32 index){
    map[index >> WIDTH] |= 1 << (index & MASK);
}

void reset_bit_in_map(u32 index){
    map[index >> WIDTH] &= ~(1 << (index & MASK));
}

boolean check_bit_in_map(u32 index){
    return (map[index >> WIDTH] & (1 << (index & MASK))) ? TRUE : FALSE;
}

#ifdef DEBUG_MODE

void show_bitmap(void){
    register u32            i;

    for (i = 0; i < (1 + (MAP_MAX_LENGTH >> WIDTH)); i++){
        printf("%u\t",map[i]);
    }
    printf("\n");
}

#endif
