#include "myalgorithm.h"
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

int get_max_int_bit(void){
    unsigned int            integer = ~0;
    int                     counter;

    for(counter = 0; integer; integer >>= 1, counter ++);

    return counter;
}

int get_max_long_bit(void){
    unsigned long           long_integer = ~0;
    int                     counter;

    for(counter = 0; long_integer; long_integer >>= 1, counter ++);

    return counter;
}

int get_max_long_long_bit(void){
    unsigned long long      long_long_integer = ~0;
    int                     counter;

    for(counter = 0; 
        long_long_integer; long_long_integer >>= 1, counter ++);

    return counter;
}

void set_bit(unsigned *address, int n){
    unsigned                temp = *address;

    /* n should start from 1 */
    if (n < 1){
        fprintf(stderr, "Invalid input: %d\n", n);
        return;
    }

    /* Make sure this type has enough place to store n bits */
    if (!(temp |= (~0 << n))){
        fprintf(stderr, 
            "Error: unsigned int has no room for %d bits. \
                -- This is set-bit() from bit_operation speaking.\n", n);
        return;
    }

    *address |= 1 << (n-1);
    return;
 }

void set_bits(unsigned *address, ...){
    va_list                 va_ptr;
    int                     set_on, mask = 0;

    fprintf(stderr, "Warning: va_list is used. \
                -- This is set-bits() from bit_operation speaking.\n");

    va_start(va_ptr, address);
    while (*va_ptr){
        set_on = va_arg(va_ptr, int);

        if ((set_on <= 0) || (set_on > 64)){
            break;
        }
        
        /* Only handle 1~32 bits */
        if (set_on > 32){
            fprintf(stderr,
                "Warning: %d will be ignored. \
                -- This is set-bits() from bit_operation speaking.\n",
                set_on);
            continue;
        }

        mask += 1 << (set_on - 1);
    }

    *address |= mask;
    return;
}

/* The function below is copied from K&R */
unsigned get_bits(unsigned x, int p, int n){
    return (x >> (p + 1 - n) & ~(~0 << n));
}

/*
 * This function is used to get ones in bit-format number
 */
int count_ones(int number){
    int                     ret = 0;

    while (number){
        ret++;
        /*
         * This will walk from right to left to count a "one" at a time and
         * and ignore all zeros at a time. e.g.:
         *
         * We have 11 (1011, 3 "1" in it)
         *
         * Step 1:
         *          number = 11     |:bit-format:|-> 1011
         *          number -1 = 10  |:bit-format:|-> 1010
         *          number & (number -1)      |::|-> 1010
         *  Thus, after one step, the last bit has been handled.
         *
         * Step 2:
         *          number = 10     |:bit-format:|-> 1010
         *          number-1 = 9    |:bit-format:|-> 1001
         *          number &(number-1)        |::|-> 1000
         *  Thus, after another step, only one "one" left. So, this is much
         *  better than ">>" operation. It needs 3 steps in total.
         *
         * Reason:
         *  The operation "-1" will turn every 0 bit to its oppsite(1). So
         *  it can skip muti-zeros at a time, and 1 is the only thing that
         *  make sense to it.
         *
         */
        number &= (number-1);
    }
    return ret;
}
