#include "myutilities.h"
#include "mytypes.h"
#include <string.h>

#define MAX_PATTERN_LENGTH  100

u32                         next[MAX_PATTERN_LENGTH];

void get_next (char pattern[])
{
    u32                     length;
    u32                     k;
    u32                     q;

    k = 0;
    length = strlen (pattern);
    for (q = 1; q < length -1 ; q++)
    {
        while ((k) && (pattern[k+1] != pattern[q])) 
        {
             k = next[k];
        }

        if (pattern[k+1] == pattern[q])
        {
            k++;
        }

        next[q] = k;
    }
}

s32 KMP_matcher (char text[], char pattern[])
{
    u32                     m;
    u32                     n;
    u32                     q;
    u32                     i;

    n = strlen (text);
    m = strlen (pattern);
    get_next (pattern);
    for (i = 0; i < n; i++)
    {
        while ((q) && (pattern[q+1] != text[i]))
        {
            q = next[q];
        }

        if (pattern[q+1] == text[i])
        {
            q++;
        }

        if (q == m)
        {
            return (i-m);
        }

        q = next[q];
    }

    return -1;
}
