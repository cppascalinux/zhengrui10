#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define ll long long
#define mod 1000000007
using namespace std;
int n,m,smq,ans;
int nxt[100009];
int p[100009],vis[100009];
int f[100009];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)
			ans=(ll)ans*a%mod;
	return ans;
}
int fnd(int x)
{
	return x==f[x]?x:f[x]=fnd(f[x]);
}
void solve()
{
	for(int i=1;i<=n;i++)
		if(p[nxt[i]]!=nxt[p[i]])
			return;
	smq++;
	for(int i=1;i<=n;i++)
		f[i]=i;
	for(int i=1;i<=n;i++)
		f[fnd(i)]=fnd(p[i]);
	int smp=0;
	for(int i=1;i<=n;i++)
		smp+=i==f[i];
	ans=(ans+qpow(m,smp))%mod;
}
void dfs(int d)
{
	if(d>n)
	{
		solve();
		return;
	}
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			vis[i]=1;
			p[d]=i;
			dfs(d+1);
			vis[i]=0;
		}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",nxt+i);
	dfs(1);
	printf("%lld",(ll)ans*qpow(smq,mod-2)%mod);
	// cerr<<clock();
	return 0;
}