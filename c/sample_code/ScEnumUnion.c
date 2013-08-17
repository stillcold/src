#include <stdio.h>

/*
 * This can be treated as a standard program about enum and union.
 */

int main(void){
    enum my_enum{a, b};

    /* Don't forget the second ";", otherwise, there will be a warning */
    union my_union{unsigned int uns_int; short short_int[2];} MY_UNION;

    /* Now can access b directly instead of *.b */
    MY_UNION.uns_int = b;

    /*
     * In fact, this can tell the endian information.
     * My PC is little endian, MY_UNION.short_int[0] will be 1 on my PC.
     */
    printf("%d %d\n", MY_UNION.short_int[0], MY_UNION.short_int[1]);

    return 0;
}
