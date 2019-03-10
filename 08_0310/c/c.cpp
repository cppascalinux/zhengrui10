#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define inf 0x7FFFFFFF
using namespace std;
int n;
int p[300009];
int c[300009];
int mxl[300009],mxr[300009],mnl[300009],mnr[300009];
void add(int x,int val)
{
	for(;x<=n;x+=x&-x)
		c[x]+=val;
}
int ask(int x)
{
	int val=0;
	for(;x;x-=x&-x)
		val+=c[x];
	return val;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",p+i);
	for(int i=1;i<=n;i++)
	{
		mnl[i]=ask(p[i]);
		mxl[i]=i-1-mnl[i];
		add(p[i],1);
	}
	memset(c,0,sizeof(c));
	for(int i=n;i>=1;i--)
	{
		mnr[i]=ask(p[i]);
		mxr[i]=n-i-mnr[i];
		add(p[i],1);
	}
	int pl=inf,pr=inf;
	for(int i=1;i<=n;i++)
	{
		int npl=i-1-mxl[i]+mnl[i]-2*p[i];
		int npr=n-i-mnr[i]+mxr[i]+2*p[i];
		pl=min(pl,npl);
		pr=min(pr,npr);
	}
	ll ans=0;
	for(int i=1;i<=n;i++)
		ans+=mxl[i];
	int t=min(pl+pr+2,0);
	printf("%lld",ans+t);
	return 0;
}