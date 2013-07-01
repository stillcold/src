#include <stdio.h>

/*
 * This code indicates that enum type is in fact treadted as integer type.
 * It begins from zero, and increse itself later.
 */

int main(void)
{
    typedef enum e1
    {
        zero,
        one,
        two,
        three
    } num;

    /* Note: "one" is the second index here. enum starts from 0. */
    num num_one = one;
    num num_two = two;
    num num_three = three;

    printf("%d\n", num_one);
    printf("%d\n", num_two);
    printf("%d\n", num_three);
    
    return 0;
}
