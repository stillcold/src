#include "myutilities.h"
#include "mytypes.h"

/* Seems that month[][] can't work, neither can month[2][] */

static u8 days_of_month[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

static char *month_name[] = {
    "Illegal name",
    "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"
};

boolean is_leap_year(u16 year){
    if (year % 400 == 0)
        return TRUE;
    if ((year % 4 == 0) && (year % 100 != 0))
        return TRUE;
    return FALSE;
}

u16 get_day_of_year(DATE_AND_TIME date_and_time){
    register int            i;
    int                     is_leap = 0;
    u16                     ret = 0;

    if (date_and_time.month <= 2){
        for (i = 1; i < date_and_time.month; i++){
            ret += days_of_month[0][i-1];
        }

        return (ret + date_and_time.date);
    }

    if (is_leap_year(date_and_time.year))
        is_leap = 1;

    for (i = 1; i < date_and_time.month; i++){
          ret += days_of_month[is_leap][i-1];
    }

    return (ret + date_and_time.date);
}

char *get_month_name(DATE_AND_TIME date_and_time){
    return (date_and_time.month < 1 || date_and_time.month > 12) ?
        month_name[0] : month_name[date_and_time.month];
}
