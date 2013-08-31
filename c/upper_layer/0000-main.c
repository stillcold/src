#include "myutilities.h"
#include <stdio.h>

int                         i;

void init(void);

extern int                  heap[HEAP_MAX_LENGTH];

void init(void){
    heap[0] = 5;
    heap[1] = 4;
    heap[2] = 1;
    heap[3] = 2;
    heap[4] = 0;
    heap[5] = 3;
    heap[6] = 9;
    heap[7] = 7;
    heap[8] = 8;
    heap[9] = 6;
}

int main(void){
    init();

    for(i = 0; i < 10; i++){
        printf("%d\t",heap[i]);
    }
    printf("\n");

    heap_sort(10);

    for(i = 0; i < 10; i++){
        printf("%d\t",heap[i]);
    }
    printf("\n");

    return 0;
}
