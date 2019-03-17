#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define ll long long
#define mod 1000000007
using namespace std;
int n,m,sm,ans;
int v[10009],st[10009],tp;
int b[10009];
int vis[3700000];
int grt[3700000][6];
ll po[3700000][6];
void init()
{
	for(int i=1;i<=sm;i++)
	{
		ll t=i;
		for(int j=2;j<=5;j++)
		{
			t*=i;
			if(t>sm)
				break;
			grt[t][j]=i;
		}
	}
	for(int i=1;i<=sm;i++)
	{
		po[i][0]=1;
		for(int j=1;j<=5;j++)
			po[i][j]=po[i][j-1]*i;
	}
	// for(int i=1;i<=sm;i++)
	// 	for(int j=0;j<=5;j++)
	// 		printf("i:%d j:%d rt:%d\n",i,j,grt[i][j]);
}
void solve(ll x)
{
	if(x>sm)
		return;
	if(sm%x!=0)
		return;
	int t=sm/x;
	int rt=grt[t][v[m]];
	if(rt&&vis[rt])
		ans++;
}
void dfs(int d,ll mul)
{
	if(mul>sm)
		return;
	if(d>m-1)
	{
		solve(mul);
		return;
	}
	for(int i=1;i<=tp;i++)
		dfs(d+1,mul*po[st[i]][v[d]]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d",v+i);
	sm=1;
	for(int i=1;i<=n;i++)
		sm*=i;
	for(int i=1;i<=sm;i++)
		if(sm%i==0)
		{
			st[++tp]=i;
			vis[i]=1;
		}
	// printf("tp:%d\n",tp);
	init();
	dfs(1,1);
	printf("%d",ans);
	return 0;
}