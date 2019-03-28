//zroj607 算算算 斯特林数
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 1000000007
#define ll long long
using namespace std;
int n,k;
char ss[50009];
int v[50009],s[109][109],cb[109][109];
int f[50009][109],mul[109],tmp[109];
int ans[50009];
void init()
{
	for(int i=0;i<=100;i++)
	{
		s[i][0]=0;
		s[i][i]=1;
	}
	for(int i=2;i<=100;i++)
		for(int j=1;j<i;j++)
			s[i][j]=(s[i-1][j-1]+(ll)s[i-1][j]*j)%mod;
	for(int i=0;i<=100;i++)
		cb[i][i]=cb[i][0]=1;
	for(int i=2;i<=100;i++)
		for(int j=1;j<i;j++)
			cb[i][j]=(cb[i-1][j-1]+cb[i-1][j])%mod;
	// for(int i=0;i<=100;i++)
	// {
	// 	for(int j=0;j<=i;j++)
	// 		printf("%d ",s[i][j]);
	// 	printf("\n");
	// }
	mul[0]=1;
	for(int i=1;i<=100;i++)
		mul[i]=(ll)mul[i-1]*i%mod;
}
void solve()
{
	// f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=k;j++)
			f[i][j]=f[i-1][j];
		f[i][0]=(f[i][0]+1)%mod;
		for(int j=1;j<=v[i];j++)
		{
			tmp[0]=f[i][0];
			for(int l=1;l<=k;l++)
				tmp[l]=(f[i][l]+f[i][l-1])%mod;
			for(int l=0;l<=k;l++)
				f[i][l]=tmp[l];
		}
		int ans=0;
		for(int j=1;j<=k;j++)
			ans=(ans+(ll)f[i][j]*s[k][j]%mod*mul[j])%mod;
		printf("%d ",ans);
	}
	printf("\n");
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a1.out","w",stdout);
#endif
	init();
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%s",&n,&k,ss+1);
		for(int i=1;i<=n;i++)
			v[i]=ss[i]-'0';
		solve();
	}
	return 0;
}