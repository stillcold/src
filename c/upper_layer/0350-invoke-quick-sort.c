#include "myutilities.h"
#include <stdio.h>

boolean compare_int (void *target, int offset_1, int offset_2);

void swap_int (void *target, int offset_1, int offset_2);

int main(void){
    int                     index;
    /* Target */
    int                     numbers[10] = {7,1,2,4,3,8,9,0,6,5};
    int                     length = sizeof(numbers)/sizeof(int);

    sort (compare_int, swap_int, (void *)numbers, length);
    for (index=0; index < length; index++){
        printf ("%*d",3,numbers[index]);
    }

    printf ("\n");

    return 0;
}

boolean compare_int (void *target, int offset_1, int offset_2)
{
    if (*((int *)target + offset_1) >= *((int *)target + offset_2))
    {
        return TRUE;
    }
    return FALSE;
}
void swap_int (void *target, int offset_1, int offset_2)
{
    *((int *)target + offset_1) ^= *((int *)target + offset_2);
    *((int *)target + offset_2) ^= *((int *)target + offset_1);
    *((int *)target + offset_1) ^= *((int *)target + offset_2);
}
