#include "stdio.h"
#define bool int
#define true 1
#define false 0
bool isLeapYear(int year){
	if(!(year%100))
	{
		if(!(year%400))
		{
			return true;
		}
		else{
			return false;
		}
	}
	if(!(year%4))
	{
		return true;
	}
	return false;
}
int getLeapYearNum(int yearA, int yearB)
{
	int i;
	int ret = 0;
	for(i = yearA; i <= yearB; i++)
	{
		if(isLeapYear(i))
		{
			ret += 1;
		}
	}
	return ret;
}
int main(){
	printf("Begin calculate...\n");
	int ret = 0;
	int yearA = 1;
	int yearB = 2000;
	int total_year_num = yearB- yearA + 1;
	int leap_year_num = getLeapYearNum(yearA, yearB);
	int total_number_of_days = leap_year_num*366 + (total_year_num - leap_year_num) * 365;
	int total_nor_month = total_year_num * 11;
	int february_num = total_year_num;
	int total_week_num = total_number_of_days / 7;
	int difference = total_number_of_days - (total_nor_month * 22 + february_num * 20 + total_week_num*2);
	printf("\
                total year number is: %d\n\
                so we got %d februaries\n\
                and %d normal monthes\n\
                leap year num is %d\n\
                totally, we have %d days\n\
                and %d weeks\n\
                asume that normal month has 22 workdays and february has 20.\n\
then the difference is \n\
\ttotal number of days\
 - \(number of normal monthes * 22 + number of februaries * 20\
 + number of weeks * 2\)\nequals to %d days\n",\
                total_year_num,\
                total_year_num,\
                total_nor_month,\
                leap_year_num,\
                total_number_of_days,\
                total_week_num,\
                difference
	);
	return ret;
}
