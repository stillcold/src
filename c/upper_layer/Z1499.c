#include <stdio.h>
#include <string.h>
char s[90];
int dp[100],n;
int gao(int a,int m,int c,int n);
void print(int x);

int gao(int a,int m,int c,int n)
{
    int i;
	while(s[a]=='0'&&m)a++,m--;
	while(s[c]=='0'&&n)c++,n--;
	if(m<n)
	return 1;
	if(n<m)
	return 0;
	for(i=0;i<m;i++)
	{
		if(s[c+i]>s[a+i])return 1;
		if(s[c+i]<s[a+i])return 0;
	}
	return 0;
}
void print(int x)
{
    int i;
	if(x>n)
	return;
	if(x!=1)
	printf(",");
	for(i=1;i<=dp[x];i++)
	printf("%c",s[x+i-1]);
	print(x+dp[x]);
}
int main(void)
{
    int i, j, l, k;
	while(scanf("%s",s+1)&&strcmp(s+1,"0"))
	{
		dp[1]=1;
		n=strlen(s+1);
		for(i=2;i<=n;i++)
		{
			dp[i]=i;
			for(j=i-1;j>=0;j--)
			{
				if(gao(j-dp[j]+1,dp[j],j+1,i-j))
				{
					dp[i]=i-j;
					break;
				}
			}
		}
		l=n-dp[n]+1;
		dp[l]=dp[n];
		for(k=l-1;k>=1;k--)
		{
			dp[k]=-1;
			if(s[k]=='0')
			{
				dp[k]=dp[k+1]+1;
				continue;
			}
			for(j=l-1;j>=k;j--)
			{
				if(gao(k,j-k+1,j+1,dp[j+1]))
				{
					dp[k]=j-k+1;
					break;
				}
			}
		}
		print(1);
		printf("\n");
	}
	return 0;
}
