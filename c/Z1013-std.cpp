#include<cstring>
#include<iostream>
using namespace std;

const int MAX_CAP = 501;
const int MAX_CAR = 101;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt+", stdout);
#endif

    int carNo;
    int m[2][MAX_CAP][MAX_CAP];
    int wn[MAX_CAR], ws[MAX_CAR];
    int helm[3], armor[3], boot[3];
    int c1, c2, c3, d4;
    int index = 1;
    while(cin >> carNo)
    {
        if(!carNo)
        {
            break;
        }
        cin >> helm[0] >> helm[1] >> helm[2];
        cin >> armor[0] >> armor[1] >> armor[2];
        cin >> boot[0] >> boot[1] >> boot[2];
        cin >> c1 >> c2 >> c3 >> d4;

        for(int i=0;i<carNo;i++)
        {
            cin >> wn[i] >> ws[i];
        }

        int maxHelm = 0, maxArmor = 0;
        int prev = 0, now =1;
        memset(m, 0, sizeof(m));
        /*
         * Take every car into consideration to get the GLOBAL max value,
         * and store that value to m[][][].
         */
        for(int loop =0;loop<carNo;loop++)
        {
            /*
             * Because bootx changes every time, m[][][] changes from the
             * very beginning to end in very loop. After every loop, the
             * value in m[][][] just means the GLOBAL dp result after
             * another new car added to the car sequence.
             */
            memset(m[now], -1, sizeof(m[now]));
            /*
             * Both i and j are in fact offset here.
             */
            int hemlx = min(wn[loop]/helm[0], ws[loop]/helm[1]);
            for(int i=0; i<=hemlx;i++)
            {
                int armorx = min( (wn[loop]-helm[0]*i)/armor[0], (ws[loop] - helm[1]*i)/armor[1]);
                for(int j=0;j<=armorx;j++)
                {
                    /* a and b are in fact the base index */
                    int bootx = min( (wn[loop] - helm[0]*i - armor[0]*j)/boot[0], (ws[loop]-helm[1]*i-armor[1]*j)/boot[1]);
                    for(int a=0;a<=maxHelm;a++)
                    {
                        for(int b=0;b<=maxArmor;b++)
                        {
                            if(m[prev][a][b] != -1)
                            {
                                /* All works are for this statement */
                                m[now][a+i][b+j] = max(m[now][a+i][b+j], m[prev][a][b] + bootx);
                            }
                        }
                    }
                }
            }
            maxHelm += hemlx;
            maxArmor += min(wn[loop]/armor[0], ws[loop]/armor[1]);
            /*
             * I have seen more than one code about 1013, this one here is
             * better than the others because this SWAP behavior. It use a
             * very simple SWAP while others use a memcpy to copy old value
             * in old m[][][] to new one. Should be much better.
             */
            swap(prev, now);
        }

        int ans = 0;
        for(int i=0;i<=maxHelm;i++)
        {
            for(int j=0;j<=maxArmor;j++)
            {
                if(m[prev][i][j] < 0)
                {
                    continue;
                }
                int sets = min(min(i/c1, j/c2), m[prev][i][j]/c3);
                ans = max(ans, sets*d4 + helm[2]*(i-sets*c1) + armor[2]*(j-sets*c2) + boot[2]*(m[prev][i][j] - sets*c3));
            }
        }

        if(index >1)
        {
            cout << endl;
        }
        cout << "Case " << index++ << ": "<< ans << endl;
    }
}
