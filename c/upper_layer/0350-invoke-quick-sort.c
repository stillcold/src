#include "myutilities.h"
#include <stdio.h>

int main(void){
    int                     index;
    /* Target */
    int                     numbers[10] = {7,1,2,4,3,8,9,0,6,5};
    int                     length = sizeof(numbers)/sizeof(int);
    sort (numbers,length);
    for (index=0; index < length; index++){
        printf ("%*d",3,numbers[index]);
    }
    printf ("\n");
    
    return 0;
} 
