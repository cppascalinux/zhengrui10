//zroj608 买买买 容斥原理+状压dp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define mod 998244353
using namespace std;
int n,m,k;
int c[20];
int able[2109];
int mul[10000009],inv[10000009];
int f[13][2109],p[2109],g[13];
int qpow(int a,int b)
{
	// printf("a:%d b:%d ",a,b);
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)
			ans=(ll)ans*a%mod;
	// printf("ans:%d\n",ans);
	return ans;
}
void initable()
{
	for(int s=0;s<1<<n;s++)
	{
		int sm=0;
		for(int i=1;i<=n;i++)
			if(s&(1<<(i-1)))
				sm+=c[i];
		if(sm<=m)
			able[s]=1;
	}
}
void initcb()
{
	mul[0]=1;
	for(int i=1;i<=k;i++)
		mul[i]=(ll)mul[i-1]*i%mod;
	inv[k]=qpow(mul[k],mod-2);
	for(int i=k-1;i>=0;i--)
		inv[i]=(ll)inv[i+1]*(i+1)%mod;
	// for(int i=0;i<=k;i++)
	// 	printf("i:%d mul:%d inv:%d\n",i,mul[i],inv[i]);
}
int cb(int a,int b)
{
	if(b<0||b>a)
		return 0;
	return (ll)mul[a]*inv[b]%mod*inv[a-b]%mod;
}
int solve(int x)
{
	// printf("x:%d---------------\n",x);
	memset(p,0,sizeof(p));
	memset(g,0,sizeof(g));
	memset(f,0,sizeof(f));
	for(int s=0;s<1<<n;s++)
		p[s&x]+=able[s];
	int sm=0;
	for(int i=1;i<=n;i++)
		if(x&(1<<(i-1)))
			sm++;
	f[0][0]=1;
	g[0]=1;
	for(int i=1;i<=min(sm,k);i++)
	{
		for(int s=x;s;s=(s-1)&x)
		{
			for(int w=s;w;w=(w-1)&s)
				f[i][s]=(f[i][s]+(ll)f[i-1][s^w]*p[w])%mod;
			g[i]=(g[i]+f[i][s])%mod;
		}
	}
	// for(int i=1;i<=2;i++)
	// 	for(int s=1;s<=4;s++)
	// 		printf("i:%d s:%d f:%d\n",i,s,f[i][s]);
	// for(int i=0;i<=2;i++)
	// 	printf("i:%d g:%d p:%d\n",i,g[i],p[i]);
	int ans=0;
	for(int i=0;i<=min(sm,k);i++)
		ans=(ans+(ll)cb(k,i)*qpow(p[0],k-i)%mod*g[i])%mod;
	// printf("x:%d ans:%d\n",x,ans);
	if(sm&1)
		ans=(ll)ans*(mod-1)%mod;
	return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",c+i);
	initable();
	initcb();
	int ans=0;
	for(int i=0;i<1<<n;i++)
		ans=(ans+solve(i))%mod;
	printf("%d",ans);
	return 0;
}