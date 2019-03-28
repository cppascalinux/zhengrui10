//zroj607 算算算 补集转化
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 1000000007
#define ll long long
using namespace std;
int n,k;
char ss[50009];
int s[50009];
int cb[109][109];
int p[109],np[109];
void init()
{
	for(int i=0;i<=100;i++)
		cb[i][i]=cb[i][0]=1;
	for(int i=2;i<=100;i++)
		for(int j=1;j<i;j++)
			cb[i][j]=(cb[i-1][j-1]+cb[i-1][j])%mod;
}
void solve()
{
	memset(p,0,sizeof(p));
	p[0]=1;
	for(int i=1;i<=n;i++)
	{
		np[0]=1;
		for(int j=1;j<=k;j++)
			np[j]=(ll)np[j-1]*s[i]%mod;
		int ans=0;
		for(int j=0;j<=k;j++)
			ans=(ans+(ll)cb[k][j]*np[k-j]%mod*p[j]%mod*((j&1)?mod-1:1))%mod;
		printf("%d ",ans);
		for(int j=0;j<=k;j++)
			p[j]=(p[j]+np[j])%mod;
	}
	printf("\n");
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a2.out","w",stdout);
#endif
	init();
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%s",&n,&k,ss+1);
		for(int i=1;i<=n;i++)
			s[i]=s[i-1]+ss[i]-'0';
		solve();
	}
	return 0;
}