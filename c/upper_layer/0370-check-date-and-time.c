#include "myutilities.h"
#include <stdio.h>

int main(void){
    DATE_AND_TIME date_and_time = {.year = 2013, .month = 8, .date = 8};
    printf("%d\n", get_day_of_year(date_and_time));
    printf("%s\n", get_month_name(date_and_time));

    return 0;
}
