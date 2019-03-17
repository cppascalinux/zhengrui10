#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 998244353
using namespace std;
int n,m,ans;
int mat[1009][1009];
int c[1000009];
void init()
{
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			for(int k=j+1;k<=n;k++)
				if(mat[i][j]&&mat[i][k])
					mat[j][k]=mat[k][j]=1;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(!mat[i][j])
				printf("%d %d\n",i,j);
}
void solve()
{
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(c[i]==c[j]&&mat[i][j])
				return;
	// for(int i=1;i<=n;i++)
	// 	printf("%d ",c[i]);
	// printf("\n");
	ans++;
}
void dfs(int d)
{
	if(d>n)
	{
		solve();
		return;
	}
	for(int i=1;i<=n;i++)
	{
		c[d]=i;
		dfs(d+1);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		mat[a][b]=mat[b][a]=1;
	}
	init();
	dfs(1);
	printf("%d",ans);
	return 0;
}