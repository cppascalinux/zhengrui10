#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
#include<ctime>
#define pii pair<int,int>
#define fi first
#define se second
#define inf 0x7F7F7F7F
using namespace std;
int n,m,sme,ans=inf;
int t[109];
int e[109][109];
int dis[109];
pii w[10009];
void solve(int s)
{
	for(int i=1;i<=sme;i++)
		if(s&(1<<(i-1)))
			e[w[i].fi][w[i].se]=e[w[i].se][w[i].fi]=1;
	queue<int> q;
	memset(dis+1,0,n<<2);
	q.push(1);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=2;i<=n;i++)
			if(e[x][i]&&!dis[i])
			{
				dis[i]=dis[x]+1;
				q.push(i);
			}
	}
	int sm=0;
	for(int i=1;i<=n;i++)
		sm+=(int)(10*log(233*(dis[i]-t[i])*(dis[i]-t[i])+1));
	ans=min(ans,sm);
	for(int i=1;i<=sme;i++)
		if(s&(1<<(i-1)))
			e[w[i].fi][w[i].se]=e[w[i].se][w[i].fi]=0;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",t+i);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		e[a][b]=e[b][a]=1;
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(!e[i][j])
				w[++sme]=pii(i,j);
	for(int s=0;s<1<<sme;s++)
		solve(s);
	printf("%d",ans);
	cerr<<clock();
	return 0;
}