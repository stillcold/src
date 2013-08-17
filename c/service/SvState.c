#include <stdio.h>

#include "mystates.h"

static void print_info(u8 level);

void decode_state(STATE state){
    /* In fact, 1 is just OK, it is for fun and useless */
    u8                      one = 01;
    u8                      level = 0x1;

    if (!state){
        print_info(0);
        return;
    }

    for (;state;){
        if(state & one){
            print_info(level);
        }
        level++;
        state >>= 1;
    }
    return;
}

static void print_info(u8 level){
    switch (level){
        case 0:
            printf("Everything OK!\n");
            break;
        case 1:
            printf("Wrong answer!\n");
            break;
        case 2:
            printf("Result not avaliable!\n");
            break;
        case 3:
            printf("Type mismatch!\n");
            break;
        default:
            return;
    }
    return;
}
