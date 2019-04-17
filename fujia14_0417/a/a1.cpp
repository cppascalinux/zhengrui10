//2019.04.17
//zroj643 圈草地 二位数点+扫描线+线段树
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,tpa,tpc;
int p[100009];
int sa[100009],sc[100009],spa[100009],spc[100009];
int l[400009],r[400009],mx[400009],lz[400009];
vector<pii> v1[100009],v2[100009];
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
void down(int a)
{
	if(lz[a])
	{
		int la=a<<1,ra=a<<1|1;
		lz[la]+=lz[a];
		lz[ra]+=lz[a];
		mx[la]+=lz[a];
		mx[ra]+=lz[a];
		lz[a]=0;
	}
}
void add(int a,int ll,int rr,int val)
{
	if(l[a]>rr||r[a]<ll)
		return;
	if(l[a]>=ll&&r[a]<=rr)
	{
		mx[a]+=val;
		lz[a]+=val;
		return;
	}
	down(a);
	add(a<<1,ll,rr,val);
	add(a<<1|1,ll,rr,val);
	mx[a]=max(mx[a<<1],mx[a<<1|1]);
}
// int ask(int a,int ll,int rr)
// {
// 	if(l[a]>rr||r[a]<ll)
// 		return 0;
// 	if(l[a]>=ll&&r[a]<=rr)
// 		return mx[a];
// 	down(a);
// 	return max(ask(a<<1,ll,rr),ask(a<<1|1,ll,rr));
// }
void solve()
{
	int ans=0;
	build(1,1,tpc);
	for(int i=1;i<=tpa;i++)
	{
		for(int j=0;j<(int)v1[i].size();j++)
			add(1,v1[i][j].fi,v1[i][j].se,1);
		for(int j=0;j<(int)v2[i].size();j++)
			add(1,v2[i][j].fi,v2[i][j].se,-1);
		ans=max(ans,mx[1]);
	}
	if(ans==1)
		ans++;
	printf("%d",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a1.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",p+i);
	for(int i=1;i<=n;i++)
		if(p[i]>p[sa[tpa]])
			sa[++tpa]=i;
	sc[++tpc]=n;
	for(int i=n-1;i>=1;i--)
		if(p[i]<p[sc[tpc]])
			sc[++tpc]=i;
	reverse(sc+1,sc+tpc+1);
	// for(int i=1;i<=tpa;i++)
	// 	printf("i:%d sa:%d\n",i,sa[i]);
	// for(int i=1;i<=tpc;i++)
	// 	printf("i:%d sc:%d\n",i,sc[i]);
	for(int i=1;i<=tpa;i++)
		spa[i]=p[sa[i]];
	for(int i=1;i<=tpc;i++)
		spc[i]=p[sc[i]];
	for(int i=1;i<=n;i++)
	{
		int l1=lower_bound(spa+1,spa+tpa+1,p[i])-spa;
		int r1=upper_bound(sa+1,sa+tpa+1,i)-sa-1;
		int l2=lower_bound(sc+1,sc+tpc+1,i)-sc;
		int r2=upper_bound(spc+1,spc+tpc+1,p[i])-spc-1;
		// printf("i:%d l1:%d r1:%d l2:%d r2:%d\n",i,l1,r1,l2,r2);
		v1[l1].push_back(pii(l2,r2));
		v2[r1+1].push_back(pii(l2,r2));
	}
	solve();
	return 0;
}