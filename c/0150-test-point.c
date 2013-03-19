#include "stdio.h"
/*
 * Both swap1 and swap2 are OK.
 * It is hard to believe, check the postion of "*" in both function.
 * And also notice that swap2 has no return statement.
 * One more thing is:
 * 		int *a = 5; -- this is illegal.
 * 			if this can work, then the value can be exchanged easily, because it is
 *			just like an array.
 */
void swap1(int* a, int *b);
void swap2(int *a, int * b);

void swap1(int* a, int* b){
	int c;
	c = *a;
	*a = *b;
	*b = c;
	return ;
}

void swap2(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int main(void)
{
	int a = 5;
	int b = 6;
	printf("The original value:\n a = %d, b = %d\n", a, b);
	swap1(&a, &b);
	printf("%d, %d\n", a, b);
	swap2(&a, &b);
	printf("%d, %d\n", a, b);
	return 0;
}
