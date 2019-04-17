#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define inf 0x7F7F7F7F
using namespace std;
int n,m,ans=inf;
int t[109];
int w[109][109];
int dep[109];
void solve()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(dep[i]<=dep[j])
			{
				if(dep[i]<=dep[j]-2&&w[i][j])
					return;
			}
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d dep:%d\n",i,dep[i]);
	// printf("----------------------------------------------\n");
	int sm=0;
	for(int i=1;i<=n;i++)
		sm+=(int)(10*log(233*(dep[i]-t[i])*(dep[i]-t[i])+1));
	ans=min(ans,sm);
}
void dfs(int d)
{
	if(d>n)
	{
		solve();
		return;
	}
	for(int i=1;i<=n-1;i++)
	{
		dep[d]=i;
		dfs(d+1);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",t+i);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		w[a][b]=w[b][a]=1;
	}
	dfs(2);
	printf("%d",ans);
	return 0;
}