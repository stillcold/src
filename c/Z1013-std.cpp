/*
 * This code is not very good, judge by the head files, we can see both
 * stdio and iostream.
 */
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

#define ITEM_CNT    3
#define MAX_AMOUNT  500

int w[ITEM_CNT];
int s[ITEM_CNT];
int d[ITEM_CNT];

int c[ITEM_CNT];
int nDefenseOfSet;

int car[100][2];
int dp[2][MAX_AMOUNT + 1][MAX_AMOUNT + 1];

int CalcLargestDefense(int nCarCnt)
{
    int index = 0;

    memset(dp, -1, 2 * (MAX_AMOUNT + 1) * (MAX_AMOUNT + 1) * sizeof(int));

    for (int nCarIndex = 0; nCarIndex < nCarCnt; nCarIndex++)
    {
        for (int p = 0; p <= MAX_AMOUNT; p++)
        {
            if (p * w[0] > car[nCarIndex][0] || p * s[0] > car[nCarIndex][1])
            {
                break;
            }

            for (int q = 0; q <= MAX_AMOUNT; q++)
            {
                int nWeightLeft = car[nCarIndex][0] - p * w[0] - q * w[1];
                int nSizeLeft = car[nCarIndex][1] - p * s[0] - q * s[1];

                if (nWeightLeft < 0 || nSizeLeft < 0)
                {
                    break;
                }

                int m = nWeightLeft / w[2];
                if ( m > nSizeLeft / s[2])
                {
                    m = nSizeLeft / s[2];
                }

                if (nCarIndex == 0)
                {
                    dp[1 - index][p][q] = m;
                }
                else
                {
                    for (int x = p; x <= MAX_AMOUNT; x++)
                    {
                        for (int y = q; y <= MAX_AMOUNT; y++)
                        {
                            if (dp[index][x - p][y - q] >= 0)
                            {
                                if (m + dp[index][x- p][y - q] > dp[1 - index][x][y])
                                {
                                    dp[1 - index][x][y] = m + dp[index][x - p][y - q];
                                }
                            }
                        }
                    }
                }
            }
        }

        index = 1 - index;
    }

    int ret = 0;

    for (int i = 0; i <= MAX_AMOUNT; i++)
    {
        for (int j = 0; j <= MAX_AMOUNT; j++)
        {
            int k = dp[index][i][j];

            if (k >= 0)
            {
                //printf("(%d,%d)=%d\n", i, j, k);

                int t1 = i / c[0];
                int t2 = j / c[1];
                int t3 = k / c[2];

                int min = (t1 < t2) ? t1 : t2;
                min = (t3 < min) ? t3 : min;

                int temp = nDefenseOfSet * min;
                temp += (i - min * c[0]) * d[0] + (j - min * c[1]) * d[1] + (k - min * c[2]) * d[2];
                if (temp > ret)
                {
                    ret = temp;
                }
            }
        }
    }
    
    return ret;
}
int main()
{
    int nCaseCnt = 1;
    while (1)
    {
        int n;

        cin >> n;
        cin.get();

        if (n == 0)
        {
            break;
        }

        for (int i = 0; i < ITEM_CNT; i++)
        {
            cin >> w[i] >> s[i] >> d[i];
        }

        for (int i = 0; i < ITEM_CNT; i++)
        {
            cin >> c[i];
        }
        cin >> nDefenseOfSet;

        for (int i = 0; i < n; i++)
        {
            cin >> car[i][0] >> car[i][1];
        }

        int nResult = CalcLargestDefense(n);

        if (nCaseCnt > 1)
        {
            cout << endl;
        }
        cout << "Case " << nCaseCnt++ << ": " << nResult << endl;
    }

    return 0;
}

