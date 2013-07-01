#include <stdio.h>
#include <stdlib.h>

/*
 * I.M.O, The reason why C language don't have a function like substr is 
 * mostly because it has the access-by-index mechanism. Thus, anything can be
 * done in this way:
 * if there is a str a[10], and a[3,...,6] is wanted:
 *      a[0,1,2,...,9] 
 *              == strncpy(char *dest, char *src, int n) ==> 
 *      a[0,1,2,...,6]
 *              == *(a+3) ==> 
 *      a[3,...,6]
 */

int main(void)
{
    /* In ILP32, int has 4 bits*/
    typedef unsigned char       UINT8;
    typedef unsigned short      UINT16;
    typedef unsigned int        UINT32;
    
    char *src = "w9999";
    int         num0;
    UINT8       num1;
    UINT16      num2;
    UINT32      num3;

    printf("%s\n", src);
    num0 = strtoul(src+1, NULL, 0);
    num1 = (UINT8) strtoul(src+1, NULL, 0);
    num2 = (UINT16) strtoul(src+1, NULL, 0);
    num3 = (UINT32) strtoul(src+1, NULL, 0);
    printf("%d %u %u %u\n", num0, num1, num2, num3);

    return 0;
}
