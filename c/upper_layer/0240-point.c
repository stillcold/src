#include <stdio.h>

void modify(int *ptr);

int main(void)
{
    int p = 2;
    /* int *p =2 can't work. */
    modify(&p);
    printf("Addr is %x\n",p);
    return 0;
}

void modify(int *ptr)
{
    *ptr = 1;
}
