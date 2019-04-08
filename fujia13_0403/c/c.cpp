//2019.04.08
//zroj171 【18 省选 10】Blowhard 前缀和优化dp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
int n,m;
ll mt;
int w[309][309];
ll f[309][309][309];
ll mn[5][309][309];
void dp()
{
	memset(f,0x7F,sizeof(f));
	memset(f[0],0,sizeof(f[0]));
	for(int i=1;i<=n;i++)
	{
		memset(mn,0x7F,sizeof(mn));
		for(int j=m;j>=1;j--)
			for(int k=m;k>=1;k--)
				mn[1][j][k]=min(f[i-1][j][k]+mt*(j+k),min(mn[1][j+1][k],mn[1][j][k+1]));
		for(int j=1;j<=m;j++)
			for(int k=m;k>=1;k--)
				mn[2][j][k]=min(f[i-1][j][k]-mt*(j-k),min(mn[2][j-1][k],mn[2][j][k+1]));
		for(int j=1;j<=m;j++)
			for(int k=1;k<=m;k++)
				mn[3][j][k]=min(f[i-1][j][k]-mt*(j+k),min(mn[3][j-1][k],mn[3][j][k-1]));
		for(int j=m;j>=1;j--)
			for(int k=1;k<=m;k++)
				mn[4][j][k]=min(f[i-1][j][k]+mt*(j-k),min(mn[4][j+1][k],mn[4][j][k-1]));
		for(int j=1;j<=m;j++)
			for(int k=1;k<=m;k++)
				if(j!=k)
				{
					ll &p=f[i][j][k];
					p=min(p,mn[1][j][k]-mt*(j+k));
					p=min(p,mn[2][j][k]+mt*(j-k));
					p=min(p,mn[3][j][k]+mt*(j+k));
					p=min(p,mn[4][j][k]-mt*(j-k));
					p+=w[i][j]+w[i][k];
				}
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%d%d%lld",&n,&m,&mt);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",w[i]+j);
	dp();
	ll ans=f[1][0][0];
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=m;j++)
		{
			// printf("%lld ",f[n][i][j]);
			ans=min(ans,f[n][i][j]);
		}
		// printf("\n");
	}
	printf("%lld\n",ans);
	return 0;
}