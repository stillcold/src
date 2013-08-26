#include <stdio.h>
#include "myutilities.h"

int main(void){
    unsigned a = 0;
    unsigned b =-1;
    unsigned c = 0;
    unsigned d = 1;
    register int            number;

    printf("Int takes %d bits.\n", get_max_int_bit());
    printf("Long takes %d bits.\n", get_max_long_bit());
    printf("Long long takes %d bits.\n", get_max_long_long_bit());

    set_bits(&a, 32,36);
    printf("%u\n", a);
    set_bits(&a, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,36);
    printf("%u\n", a);

    printf("get -1, 8, 8 -> %u\n", get_bits(b, 8 , 8));
    printf("get 0, 8, 8 -> %u\n", get_bits(c, 8 , 8));
    printf("get 1, 8, 8 -> %u\n", get_bits(d, 8 , 8));
    printf("Test count ones:\n");
    for(number = 0; number < 33; number++){
        printf("%d has %d one(s) in it.\n", number, count_ones(number));
    }

    return 0;
}
