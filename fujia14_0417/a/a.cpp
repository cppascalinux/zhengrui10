#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 0x7F7F7F7F
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n;
int p[100009];
int mxr[100009],mnl[100009];
pii st[100009],rp[100009];
int l[400009],r[400009],mx[400009];
void init()
{
	int tp=0;
	p[n+1]=inf;
	for(int i=1;i<=n+1;i++)
	{
		while(tp&&p[i]>=st[tp].se)
		{
			mxr[st[tp].fi]=i-1;
			tp--;
		}
		st[++tp]=pii(i,p[i]);
	}
	p[0]=-inf,tp=0;
	for(int i=n;i>=0;i--)
	{
		while(tp&&p[i]<=st[tp].se)
		{
			mnl[st[tp].fi]=i+1;
			tp--;
		}
		st[++tp]=pii(i,p[i]);
	}
}
void build(int a,int ll,int rr)
{
	l[a]=ll;
	r[a]=rr;
	if(ll<rr)
	{
		int mid=(ll+rr)>>1;
		build(a<<1,ll,mid);
		build(a<<1|1,mid+1,rr);
	}
}
void add(int a,int pos,int val)
{
	if(l[a]==r[a])
	{
		mx[a]=max(mx[a],val);
		return;
	}
	if(pos<=r[a<<1])
		add(a<<1,pos,val);
	else
		add(a<<1|1,pos,val);
	mx[a]=max(mx[a<<1],mx[a<<1|1]);
}
int ask(int a,int ll,int rr)
{
	if(l[a]>rr||r[a]<ll)
		return 0;
	if(l[a]>=ll&&r[a]<=rr)
		return mx[a];
	return max(ask(a<<1,ll,rr),ask(a<<1|1,ll,rr));
}
void solve()
{
	int ans=0;
	for(int i=1;i<=n;i++)
		rp[i]=pii(mnl[i],i);
	sort(rp+1,rp+n+1);
	build(1,1,n);
	int p=0;
	for(int i=1;i<=n;i++)
	{
		while(p<n&&rp[p+1].fi<=i)
		{
			p++;
			add(1,rp[p].se,rp[p].se);
		}
		int fnr=ask(1,i,mxr[i]);
		ans=max(ans,fnr-i+1);
	}
	printf("%d",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",p+i);
	init();
	solve();
	return 0;
}