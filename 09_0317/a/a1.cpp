//zroj634 图 并查集+线段树合并/启发式合并
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define mod 998244353
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,tot,cnt;
int hd[1000009],eg[2000009],nxt[2000009];
int rt[1000009],lp[22000009],rp[22000009],sm[22000009];
int f[1000009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void add(int &a,int l,int r,int x)
{
	if(!a)
		a=++cnt;
	sm[a]++;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(x<=mid)
		add(lp[a],l,mid,x);
	else
		add(rp[a],mid+1,r,x);
}
int merge(int a,int b,int l,int r)
{
	if(a==b)
		return a;
	if(!a||!b)
		return a|b;
	if(l==r)
	{
		sm[a]=sm[a]|sm[b];
		// sm[a]=sm[a]+sm[b];
		return a;
	}
	int mid=(l+r)>>1;
	lp[a]=merge(lp[a],lp[b],l,mid);
	rp[a]=merge(rp[a],rp[b],mid+1,r);
	sm[a]=sm[lp[a]]+sm[rp[a]];
	return a;
}
int ask(int a,int l,int r,int ql,int qr)
{
	if(l>qr||r<ql)
		return 0;
	if(l>=ql&&r<=qr)
		return sm[a];
	int mid=(l+r)>>1;
	return ask(lp[a],l,mid,ql,qr)+ask(rp[a],mid+1,r,ql,qr);
}
int fnd(int x)
{
	return x==f[x]?x:f[x]=fnd(f[x]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a1.out","w",stdout);
#endif
	rd(n),rd(m);
	for(int i=1;i<=n;i++)
		f[i]=i;
	for(int i=1,a,b;i<=m;i++)
	{
		rd(a),rd(b);
		ins(a,b);
		ins(b,a);
	}
	for(int i=1;i<=n;i++)
		for(int j=hd[i];j;j=nxt[j])
			if(eg[j]>i)
				add(rt[i],1,n,eg[j]);
	ll ans=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=hd[i];j;j=nxt[j])
			if(eg[j]<i)
			{
				rt[i]=merge(rt[i],rt[fnd(eg[j])],1,n);
				f[fnd(eg[j])]=fnd(i);
			}
		int t=ask(rt[i],1,n,i+1,n);
		ans=ans*(n-t)%mod;
		// printf("i:%d ans:%lld sm:%d\n",i,ans,t);
	}
	printf("%lld",ans);
	return 0;
}