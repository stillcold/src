#include "stdio.h"
#include "stdarg.h"

typedef struct node{
    int                     a;
    char                    b;
} NODE;

void fun1 (NODE a, ...)
{
    va_list ptr;
    int next;

    va_start (ptr, a);
    do {
        next = va_arg (ptr, int);
        printf ("%d\n",next);
    }
    while (next!=-1 && next);

    va_end(ptr);
}

int main(){
    NODE a = {.a = 1, .b ='a'};
    fun1(a,1,2,3, -1);
    fun1(a);
    return 0;
}
