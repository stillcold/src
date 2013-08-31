#include "myalgorithm.h"
#include "mytypes.h"
#include <string.h>

s32                         next[MAX_PATTERN_LENGTH];

/*
 * This code has been verified, it is OK.
 */
void get_next(char pattern[])
{
    int                     k;
    int                     j;

    next[0] = -1;
    k = -1;
    j = 0;
    while (pattern[j] != '\0')
    {
        if (k!= -1 && pattern[k] != pattern[j])
            k=next[k];
        ++j;
        ++k;
        if (pattern[k] == pattern[j])
            next[j] = next[k];
        else
            next[j] = k;
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
