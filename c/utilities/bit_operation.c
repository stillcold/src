#include "myutilities.h"
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
