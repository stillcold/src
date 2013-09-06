#include "mytools.h"
#include "mytypes.h"
#include <time.h>
#include <stdlib.h>

static boolean              is_inited = FALSE;

int get_random_number(int range){
    if (!is_inited){
        srand((unsigned) time(NULL));
        is_inited = TRUE;
    }

    return rand() % range;
}
