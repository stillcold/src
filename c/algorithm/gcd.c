#include "mytypes.h"
#include "myalgorithm.h"

u32 gcd (u32 num_A, u32 num_B)
{
    if (!num_B)
    {
        return num_A;
    }

    return gcd (num_B, num_A % num_B);
}
