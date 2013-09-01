#ifndef _MYTOOLS_H_
#define _MYTOOLS_H_

#include "myconfig.h"
#include "mytypes.h"

#include <sys/time.h>

#define                     MAX_RAND_NUMBER 10000

typedef struct date_and_time {
    u16                     year;
    u8                      month;
    u8                      date;
    u8                      week;
    u8                      hour;
    u8                      minute;
    u8                      second;
} DATE_AND_TIME; 


/**************************************************************************
 *
 * time_and_date.c
 *
 * DESCRIPTION:
 *              Use it in this way:
 *                  get_day_of_year(.year = 2013, .month = 1, .day = 3)
 *                          -> 3
 *
 *************************************************************************/

u16 get_day_of_year(DATE_AND_TIME date_and_time);


/**************************************************************************
 *
 * time_and_date.c
 *
 *************************************************************************/

boolean is_leap_year(u16 year);


/**************************************************************************
 *
 * time_and_date.c
 *
 *************************************************************************/

char *get_month_name(DATE_AND_TIME date_and_time);

void mark_start(void);

void mark_stop(void);

void get_time_difference(struct timeval *diff);

/**************************************************************************
 *
 * tlrandnumber.c
 *
 *************************************************************************/
int get_rand_number(int range);

#endif /* _MYSTATES_H_ */
