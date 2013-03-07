#include "stdio.h"
/* case number */
int round;
/* number of Caravan.*/
int num;
/* weight, size and defend capability of helm. */
int w1, s1, d1;
/* armor */
int w2, s2, d2;
/* boot */
int w3, s3, d3;
/* c1-c3: number of helm, armor and boot in each set, d4: capability of set. */
int c1, c2, c3, d4;
/* size and weight of each Caravan. */
int x, y;
unsigned int i;

int main(void)
{
	while (scanf("%d", &num) & num)
	{
		scanf("%d %d %d", &w1, &s1, &d1);
		scanf("%d %d %d", &w2, &s2, &d2);
		scanf("%d %d %d", &w3, &s3, &d3);
		scanf("%d %d %d %d", &c1, &c2, &c3, &d4);
		for (i = 0; i < num; i++) {
			scanf("%d %d", &x, &y);
		}
	}
    return 0;
}
