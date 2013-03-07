#include "stdio.h"
#include "stdarg.h"

void fun1(int a, ...){
    va_list ptr;
    va_list pt2;
    va_list pt3;
    *pt3 = *ptr;
    int next = a;
    va_start(ptr, a);
    va_copy(pt2, ptr);
    do {
	printf("%d\n",next);
	next = va_arg(ptr,int);
    }while(next!=-1);
    va_end(ptr);
    /*do {
	printf("%d\n",next);
	next = va_arg(pt2,int);
    }while(next!=-1);
    va_end(pt2);*/
    do {
	printf("%d\n",next);
	next = va_arg(pt3,int);
    }while(next!=-1);
}

int main(){
    fun1(1,2,3, -1);
    return 0;
}
