#include "stdio.h"

#define true 1
#define false 0

typedef int boolean;

static boolean sort(int* , int, ...);

static boolean qsort(int*, int , int );

int main(void){
    int index;
    int numbers[10]={7,1,2,4,3,8,9,0,6,5};//target to be sorted.
    int length = sizeof(numbers)/sizeof(int);
    sort(numbers,length);
    for(index=0; index < length; index++){
        printf("%*d",3,numbers[index]);
    }
    printf("\n");
    return 0;
}

/*
 * Function: qsort
 * return:
 *     0: function works properly.
 *     none-0: function occurs an error.
 * parameters:
 *     target: name of the array.
 *     low: index of the first element, starts from 0.
 *     high: indext of the last elemnt, end at length-1.
 */
boolean qsort(int* target, int low, int high){
    int offsetl = low;
    int offseth = high;

    int ref = *(target+low);
    int temp;
    int ret = 0;

    if (offsetl > offseth){
        return -1;
    }

    if (offsetl == offseth){
        return 0;
    }

    while (offsetl < offseth){
        while (*(target+offseth) >= ref && offsetl < offseth) offseth--;
        while (*(target+offsetl) <= ref && offsetl < offseth) offsetl++;

        temp = *(target+offsetl);
        *(target+offsetl) = *(target+offseth);
        *(target+offseth) = temp;
    }

    temp = *(target+offsetl);
    *(target+offsetl) = ref;
    *(target+low) = temp;

    if(low!=offsetl){
        ret = qsort(target, low, offsetl);
    }
    if(high!=offsetl+1){
        ret = qsort(target, offsetl+1, high);
    }

    return ret;
}

boolean sort(int* target, int length, ...){
    return qsort(target, 0, length-1);
}
