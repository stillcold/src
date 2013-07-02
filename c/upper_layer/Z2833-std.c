#include<stdio.h>
#include<string.h>
#define MAXN 100005
int head[MAXN],sum[MAXN];

int find(int a);
void com(int a,int b);

int find(int a)
{
    int x=a;
    if (head[x]!=x) head[x]=find(head[x]);
    return head[x];
}
void com(int a,int b)
{
    head[find(b)]=head[find(a)];
}

int main(void)
{
    int m,n,i,a,b,cas=1;
    char op;
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        if (cas!=1) printf("/n");
        printf("Case %d:/n",cas++);
        getchar();
        for (i=1;i<=n;++i) {head[i]=i;sum[i]=1;}
        for (i=1;i<=m;++i)
        {
            scanf("%c",&op);
            if (op=='M')
            {
                scanf("%d%d",&a,&b);
                if (find(a)!=find(b)) 
                {
                    sum[find(a)]+=sum[find(b)];
                    com(a,b);
                }
            }
            if (op=='Q')
            {
                scanf("%d",&a);
                printf("%d/n",sum[find(a)]);
            }
            getchar();
        }
    }
    return 0;
}

