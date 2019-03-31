//zroj642 树 分块+二分答案
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,m,tot,tme,cnt;
int hd[50009],eg[100009],nxt[100009],len[100009];
int dfn[50009],id[50009],ed[50009];
pii v[50009],st1[50009],st2[50009];
int bel[50009];
int l[5009],r[5009],lz[5009];
int ans[50009];
void ins(int a,int b,int c)
{
	eg[++tot]=b;
	len[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs1(int x,int fa,int sm)
{
	ed[x]=dfn[x]=++tme;
	id[tme]=x;
	v[tme]=pii(sm,tme);
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			dfs1(eg[i],x,sm+len[i]);
			ed[x]=max(ed[x],ed[eg[i]]);
		}
}
void init()
{
	int len=min(n,(int)(sqrt(n*20)+0.5));
	for(int i=1;i<=n;i++)
	{
		if(i>r[cnt])
		{
			l[++cnt]=i;
			r[cnt]=min(l[cnt]+len-1,n);
		}
		bel[i]=cnt;
	}
	for(int i=1;i<=cnt;i++)
		sort(v+l[i],v+r[i]+1);
}
int judge(int x)
{
	int ans=0;
	for(int i=1;i<=cnt;i++)
		ans+=lower_bound(v+l[i],v+r[i]+1,pii(x-lz[i],-1))-v-l[i];
	return ans+1;
}
int ask()
{
	int l=0,r=500000000,mid;
	while(l<r)
	{
		mid=(l+r+1)>>1;
		if(judge(mid)<=m)
			l=mid;
		else
			r=mid-1;
	}
	return l;
}
void rebuild(int id,int lp,int rp,int val)
{
	int tp1=0,tp2=0;
	for(int i=l[id];i<=r[id];i++)
		if(v[i].se>=lp&&v[i].se<=rp)
			st1[++tp1]=pii(v[i].fi+val,v[i].se);
		else
			st2[++tp2]=v[i];
	int sp1=0,sp2=0,spv=l[id]-1;
	while(sp1<tp1&&sp2<tp2)
		v[++spv]=st1[sp1+1]<st2[sp2+1]?st1[++sp1]:st2[++sp2];
	while(sp1<tp1)
		v[++spv]=st1[++sp1];
	while(sp2<tp2)
		v[++spv]=st2[++sp2];
}
void add(int lp,int rp,int val)
{
	if(lp>rp)
		return;
	int bl=bel[lp],br=bel[rp];
	if(bl==br)
	{
		rebuild(bl,lp,rp,val);
		return;
	}
	for(int i=bl+1;i<=br-1;i++)
		lz[i]+=val;
	rebuild(bl,lp,r[bl],val);
	rebuild(br,l[br],rp,val);
}
void dfs2(int x,int fa)
{
	ans[x]=ask();
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			int lp=dfn[eg[i]],rp=ed[eg[i]];
			add(1,lp-1,len[i]);
			add(rp+1,n,len[i]);
			add(lp,rp,-len[i]);
			dfs2(eg[i],x);
			add(1,lp-1,-len[i]);
			add(rp+1,n,-len[i]);
			add(lp,rp,len[i]);
		}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	m++;
	for(int i=1,a,b,c;i<=n-1;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		ins(a,b,c);
		ins(b,a,c);
	}
	dfs1(1,0,0);
	init();
	dfs2(1,0);
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}