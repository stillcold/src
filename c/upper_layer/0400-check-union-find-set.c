#include "mystructures.h"
#include <stdio.h>

int main(void){
    UF_set_init();
    UF_set_create(1);
    UF_set_create(2);
    UF_set_create(3);
    UF_set_create(5);
    UF_set_create(1);
    UF_set_create(4);
    UF_set_create(6);
    UF_set_create(7);
    UF_set_create(1);
    UF_set_create(8);
    UF_set_create(9);
    UF_set_create(0);
    UF_set_union(1,2);
    UF_set_union(5,2);
    UF_set_union(7,5);
    UF_set_union(7,2);
    UF_set_union(1,2);

    printf("%d\n", UF_set_find(2));
    printf("%d\n", UF_set_find(3));

    printf("number: %d\n", UF_set_get_number(2));
    return 0;
}
