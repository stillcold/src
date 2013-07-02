#include "myutilities.h"
#include <stdio.h>
#include <string.h>

int main (void)
{
    int                     i;
    int                     length;
    char                    pattern[100] = "abcdaabcab";

    length = strlen (pattern);
    for ( i = 0; i < length; i ++)
    {
        printf ("%c\t", pattern[i]);
    }
    printf ("\n");
    for ( i = 0; i < length; i ++)
    {
        printf ("%d\t", i);
    }
    printf ("\n");
    for ( i = 0; i < length; i ++)
    {
        printf ("%d\t", next[i]);
    }
    printf ("\n");
    get_next (pattern);
    for ( i = 0; i < length; i ++)
    {
        printf ("%d\t", next[i]);
    }
    printf ("\n");
    return 0;
}
