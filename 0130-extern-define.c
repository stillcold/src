/*
 * Cannot be deleted, 0120 and 0140 rely on it.
 */
#include "stdio.h"
#include "0140-testExtern.h"

extern int fun2(void);

int fun1(void){
    printf("This is fun1!\n");
}

int fun2(void){
    printf("This is fun2!\n");
}
