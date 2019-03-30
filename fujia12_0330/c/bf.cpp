#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k,tot;
int hd[50009],eg[100009],nxt[100009],len[100009];
int dis[50009];
void ins(int a,int b,int c)
{
	eg[++tot]=b;
	len[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs(int x,int fa,int sm)
{
	dis[x]=sm;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
			dfs(eg[i],x,sm+len[i]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%d%d",&n,&k);
	for(int i=1,a,b,c;i<=n-1;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		ins(a,b,c);
		ins(b,a,c);
	}
	for(int i=1;i<=n;i++)
	{
		dfs(i,0,0);
		// for(int j=1;j<=n;j++)
		// 	printf("i:%d j:%d dis:%d\n",i,j,dis[j]);
		nth_element(dis+1,dis+k+1,dis+n+1);
		printf("%d\n",dis[k+1]);
	}
	return 0;
}