#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 1000000007
#define ll long long
using namespace std;
int n,k;
char s[50009];
int v[50009],pw[10][109];
int cb[109][109];
int ans[50009],f[50009][109];
void init()
{
	for(int i=0;i<=100;i++)
		cb[i][i]=cb[i][0]=1;
	for(int i=2;i<=100;i++)
		for(int j=1;j<i;j++)
			cb[i][j]=(cb[i-1][j-1]+cb[i-1][j])%mod;
	for(int i=0;i<=9;i++)
	{
		pw[i][0]=1;
		for(int j=1;j<=100;j++)
			pw[i][j]=(ll)pw[i][j-1]*i%mod;
	}
}
void solve()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=k;j++)
			f[i][j]=pw[v[i]][j];
		for(int j=0;j<=k;j++)
			for(int l=0;l<=j;l++)
				f[i][j]=(f[i][j]+(ll)cb[j][l]*pw[v[i]][l]%mod*f[i-1][j-l])%mod;
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int t;
	scanf("%d",&t);
	init();
	while(t--)
	{
		scanf("%d%d",&n,&k);
		scanf("%s",s+1);
		for(int i=1;i<=n;i++)
			v[i]=s[i]-'0';
		solve();
		for(int i=1;i<=n;i++)
			printf("%d ",f[i][k]);
		printf("\n");
	}
	return 0;
}