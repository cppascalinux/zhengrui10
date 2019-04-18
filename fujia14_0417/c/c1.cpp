#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define ll long long
#define bse 3
#define mod1 1000000007
#define mod2 1000000009
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
int n,m,tot;
int nxt[100009];
int vis[100009],st[100009],tp;
int onc[100009],stc[100009],smc;
int sz[100009],f[100009],fc[100009];
int inv[100009],fail[100009];
pii mul[200009],hs[100009],sc[100009];
int pl[100009];
vector<int> v[100009];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod1)
		if(b&1)
			ans=(ll)ans*a%mod1;
	return ans;
}
void dfs0(int x)
{
	// printf("x:%d nxt:%d\n",x,nxt[x]);
	// fflush(stdout);
	if(vis[x])
	{
		for(int i=tp;st[i+1]!=x;i--)
		{
			onc[st[i]]=1;
			stc[++smc]=st[i];
		}
		return;
	}
	vis[x]=1;
	st[++tp]=x;
	dfs0(nxt[x]);
	tp--;
}
pii cal(pii p,int ml,int ad)
{
	p.fi=((ll)p.fi*ml+ad)%mod1;
	p.se=((ll)p.se*ml+ad)%mod2;
	return p;
}
pii cal(pii p,pii ml,pii ad)
{
	p.fi=((ll)p.fi*ml.fi+ad.fi)%mod1;
	p.se=((ll)p.se*ml.se+ad.se)%mod2;
	return p;
}
void init()
{
	mul[0]=pii(1,1);
	for(int i=1;i<=2*n;i++)
		mul[i]=cal(mul[i-1],bse,0);
	inv[1]=1;
	for(int i=2;i<=n;i++)
		inv[i]=(ll)(mod1-mod1/i)*inv[mod1%i]%mod1;
}
bool cmp(int a,int b)
{
	return sz[a]<sz[b]||(sz[a]==sz[b]&&hs[a]<hs[b]);
}
int cb(int a,int b)
{
	if(b>a||n<0)
		return 0;
	if(b>a-b)
		b=a-b;
	int ans=1;
	for(int i=1;i<=b;i++)
		ans=(ll)ans*(a-i+1)%mod1*inv[i]%mod1;
	return ans;
}
void dfs1(int x)
{
	sz[x]=1;
	for(int i=0;i<(int)v[x].size();i++)
	{
		int p=v[x][i];
		dfs1(p);
		sz[x]+=sz[p];
	}
	sort(v[x].begin(),v[x].end(),cmp);
	int sm=0,tf=0;
	f[x]=m;
	for(int i=0;i<(int)v[x].size();i++)
	{
		int p=v[x][i];
		if(i&&hs[p]!=hs[v[x][i-1]])
		{
			f[x]=(ll)f[x]*cb(tf+sm-1,sm)%mod1;
			sm=0;
		}
		sm++;
		tf=f[p];
	}
	if(sm)
		f[x]=(ll)f[x]*cb(tf+sm-1,sm)%mod1;
	hs[x]=pii(1,1);
	for(int i=0;i<(int)v[x].size();i++)
	{
		int p=v[x][i];
		hs[x]=cal(hs[x],mul[sz[p]*2],hs[p]);
	}
	hs[x]=cal(hs[x],bse,2);
}
void kmp()
{
	int j=0;
	for(int i=2;i<=smc;i++)
	{
		while(j&&sc[j+1]!=sc[i])
			j=fail[j];
		j+=sc[j+1]==sc[i];
		fail[i]=j;
	}
}
int gcd(int a,int b)
{
	return !b?a:gcd(b,a%b);
}
void solve()
{
	for(int i=1;i<=smc;i++)
		sc[i]=hs[stc[i]],fc[i]=f[stc[i]];
	kmp();
	if(smc%(smc-fail[smc])!=0)
	{
		int ans=1;
		for(int i=1;i<=smc;i++)
			ans=(ll)ans*fc[i]%mod1;
		printf("%d",ans);
	}
	int len=smc-fail[smc],tms=smc/len;
	// printf("len:%d tms:%d\n",len,tms);
	pl[0]=pl[1]=1;
	for(int i=1;i<=len;i++)
		pl[1]=(ll)pl[1]*fc[i]%mod1;
	for(int i=2;i<=tms;i++)
		pl[i]=(ll)pl[i-1]*pl[1]%mod1;
	// for(int i=1;i<=tms;i++)
		// printf("i:%d pl:%d\n",i,pl[i]);
	int ans=0;
	for(int i=1;i<=tms;i++)
	{
		int g=gcd(i,tms);
		// printf("g:%d\n",g);
		ans=(ans+pl[g])%mod1;
	}
	printf("%lld",(ll)ans*qpow(tms,mod1-2)%mod1);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c1.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",nxt+i);
	dfs0(1);
	// for(int i=1;i<=smc;i++)
	// 	printf("i:%d stc:%d\n",i,stc[i]);
	for(int i=1;i<=n;i++)
		if(!onc[i])
			v[nxt[i]].pb(i);
	init();
	for(int i=1;i<=n;i++)
		if(onc[i])
			dfs1(i);
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d sz:%d f:%d hsfi:%d hsse:%d\n",i,sz[i],f[i],hs[i].fi,hs[i].se);
	solve();
	return 0;
}