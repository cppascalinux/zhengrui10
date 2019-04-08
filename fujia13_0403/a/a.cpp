//2019.04.08
//zroj169【18 省选 10】Barbecue 分治+dfs
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define inf 0x7F7F7F7F
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,tot;
ll ans;
int hd[300009],eg[600009],nxt[600009];
int mn[300009],mx[300009],cnt[300009];
void clr()
{
	ans=tot=0;
	memset(hd,0,sizeof(hd));
}
void rd(int &x)
{
	char c=0;
	x=0;
	while(c<'0'||c>'9')
		c=gc();
	while(c>='0'&&c<='9')
		x=x*10+c-'0',c=gc();
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs(int x,int fa,int l,int r,int smx,int smn)
{
	mx[x]=smx;
	mn[x]=smn;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa&&eg[i]>=l&&eg[i]<=r)
			dfs(eg[i],x,l,r,max(smx,eg[i]),min(smn,eg[i]));
}
void solve(int l,int r)
{
	if(l>=r)
	{
		ans+=l==r;
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid-1);
	solve(mid+1,r);
	for(int i=l;i<=r;i++)
		mx[i]=inf,mn[i]=0;
	dfs(mid,0,l,r,mid,mid);
	for(int i=mid+1;i<=r;i++)
		mn[i]=min(mn[i],mn[i-1]),mx[i]=max(mx[i],mx[i-1]);
	for(int i=mid-1;i>=l;i--)
		mn[i]=min(mn[i],mn[i+1]),mx[i]=max(mx[i],mx[i+1]);
	cnt[mid-1]=0;
	for(int i=mid;i<=r;i++)
		cnt[i]=cnt[i-1]+(i==mx[i]);
	int lp=mid,rp=mid-1;
	for(int i=mid;i>=l;i--)
	{
		while(lp<r&&lp<mx[i])
			lp++;
		while(rp<r&&mn[rp+1]>=i)
			rp++;
		if(i==mn[i]&&rp>=lp)
			ans+=cnt[rp]-cnt[lp-1];
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int t;
	rd(t);
	while(t--)
	{
		rd(n);
		for(int i=1,a,b;i<=n-1;i++)
		{
			rd(a),rd(b);
			ins(a,b);
			ins(b,a);
		}
		solve(1,n);
		printf("%lld\n",ans);
		clr();
	}
	return 0;
}