#include "myalgorithm.h"
#include <stdio.h>

#define MAX_DP_ARRAY_COLUMN 10
#define MAX_DP_ARRAY_ROW    10

int dp_array[MAX_DP_ARRAY_COLUMN][MAX_DP_ARRAY_ROW];

/**************************************************************************
 *
 * This is a simple implemention of DP, see the problem details at POJ.
 *
 * The id of this problem is 3176.
 *
 *************************************************************************/

int dp_demo(int depth){
    register int            i;
    register int            j;

    for ( i = depth - 2; i >= 0; i--){
        for (j = 0; j <= i; j++){
            dp_array[i][j] += dp_array[i+1][j] > dp_array[i+1][j+1] ?
                dp_array[i+1][j] : dp_array[i+1][j+1];
        }
    }

    return dp_array[0][0];
}

void init_dp_array(void){
    dp_array[0][0] = 7;
    dp_array[1][0] = 3;
    dp_array[1][1] = 8;
    dp_array[2][0] = 8;
    dp_array[2][1] = 1;
    dp_array[2][2] = 0;
    dp_array[3][0] = 2;
    dp_array[3][1] = 7;
    dp_array[3][2] = 4;
    dp_array[3][3] = 4;
    dp_array[4][0] = 4;
    dp_array[4][1] = 5;
    dp_array[4][2] = 2;
    dp_array[4][3] = 6;
    dp_array[4][4] = 5;
}
