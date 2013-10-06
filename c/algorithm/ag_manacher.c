#include "myalgorithm.h"
#include "stdio.h"
#include "string.h"
#include "mymacros.h"

int str[ONE_THOUSAND];

void manacher_do(void)
{
    register int i;
    int mx = 0;
    int id;

    for ( i = manacher_length; str[i] != 0; i++)
        str[i] = 0; 
    for ( i = 1; i < manacher_length; i++)
    {
        if( mx > i )
            manacher_result[i] = min(manacher_result[2 * id - i],
                    manacher_result[id] + id - i);
        else
            manacher_result[i] = 1;
        for(; str[i + manacher_result[i]] == str[i-manacher_result[i]];
                manacher_result[i]++)
            ;
        if( manacher_result[i] + i > mx)
        {
            mx = manacher_result[i] + i;
            id = i;
        }
    }
}

void init_manacher(void)
{
    register int i;

    str[0] = '$';
    str[1] = '#';
    for ( i = 0; i < manacher_length; i++)
    {
        str[i*2+2] = original_manacher_str[i];
        str[i*2+3] = '#';
    }
    manacher_length = manacher_length * 2 + 2;
    original_manacher_str[manacher_length] = 0;
}
