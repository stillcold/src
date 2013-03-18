#include "stdio.h"

void swap1(int* a, int* b);
void swap2(int *a, int* b);

void swap1(int* a, int* b){
	int c;
	c = *a;
	*a = *b;
	*b = c;
	return ;
}

void swap2(int *a, int *b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}

int main(void)
{
	int* a = 5;
	int* b = 6;
	swap1(a,b);
	printf("%d , %d", *a, *b);
	return 0;
}
