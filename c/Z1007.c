#include <stdio.h>
/*
 * This code is OK. AC by server.
 */
int main(void)
{
    double sum = 0;
    double x;
    int k;
    for(x = 0.000; x <= 2.000; x += 0.001) {
        sum = 0;
        for(k= 1; k < 10000; k++) {
            sum += (1.0 - x) / (k * (k + 1) * (k + x));
        }
        sum = sum + (1 - x) / (2 * 10000 * 10000) + 1.0;
        printf("%5.3f %16.12f\n", x, sum);
    }
    return 0;
}
