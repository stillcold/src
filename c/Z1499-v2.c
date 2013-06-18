/*
 * Should use g++ to compile this one.
 */
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <limits.h>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <functional>
#include <ctype.h>
#define MAX 100
using namespace std;

char num[MAX];
int dp[MAX];
int ans[MAX];

bool check( char *lhs,int n, char *rhs,int m)
{
    char *p=lhs,*q=rhs;
    while(*p=='0' && n)
    {
        ++p;
        --n;
    }
    while(*q=='0' && m)
    {
        ++q;
        --m;
    }
    if(n<m)
        return true;
    else if(n>m)
        return false;
    for(int i=0;i<n;++i)
        if(*p<*q)
            return true;
        else if(*p>*q)
            return false;
        else
        {
            ++p;
            ++q;
        }
    return false;
}

int main(void)
{
    int ncase=1;

    while(gets(num+1))
    {
        int n=strlen(num+1)+1;
        if(n==2 && num[1]=='0')
            break;

        num[0]='0';
        memset(dp,0,sizeof(dp));
        dp[1]=1;

        //dp, from beginning to end, dp[last] is what really count.
        for(int i=2;i<n;++i)
        {
            dp[i]=i;
            for(int j=i-1;j>0;--j)
            {
                int t=i-j;
                if(check(num+j-dp[j]+1,dp[j],num+j+1,t))
                {
                    dp[i]=t;
                    break;
                }
            }
        }
        int last=n-dp[n-1];
        dp[last]=dp[n-1];


        //dp, from end to head, find answer.
        for(int i=last-1;i>0;--i)
        {
            dp[i]=-1;
            if(num[i]=='0')  
            {  
                dp[i]=dp[i+1]+1;  
                continue;  
            }  
            for(int j=last;j>i;--j)
                if(check(num+i,j-i,num+j,dp[j]))
                {
                    dp[i]=j-i;
                    break;
                }
        }

        int pos=1;
        memset(ans,0,sizeof(ans));
        while(pos<n)
        {
            ans[pos]=1;
            pos=pos+dp[pos];
        }

        for(int i=1;i<n;++i)
        {
            if(ans[i]&&i>1)
                printf(",");
            printf("%c",num[i]);
        }
        printf("\n");
    }
    return 0;
}

