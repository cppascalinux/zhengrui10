#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define inf 0x7F7F7F7F
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
struct node
{
	int id,a,b,l,r;
	node(){}
	node(int t1,int t2,int t3,int t4,int t5){id=t1,a=t2,b=t3,l=t4,r=t5;}
	bool operator <(const node &p) const
	{
		return l>p.l;
	}
};
int n,m;
char s[100009];
int buc[29];
int mnl[29][100009],mxl[29][100009];
int l[400009],r[400009],mn[400009],lz[400009];
vector<node> q[27];
pii ans[100009];
void ins(int x)
{
	int rp=0,sm=0;
	buc[0]=1;
	for(int i=1;i<=n;i++)
	{
		while(sm<x&&rp<n+1)
		{
			rp++;
			if(!buc[s[rp]])
				sm++;
			buc[s[rp]]++;
		}
		mnl[x][i]=rp;
		buc[s[i]]--;
		if(!buc[s[i]])
			sm--;
	}
}
void init()
{
	for(int i=1;i<=n;i++)
		s[i]-='a'-1;
	for(int i=1;i<=27;i++)
		ins(i);
	for(int i=1;i<=26;i++)
		for(int j=1;j<=n;j++)
			mnl[i][j]-=j-1;
	for(int i=1;i<=26;i++)
		for(int j=1;j<=n;j++)
			mxl[i][j]=mnl[i+1][j]-1;
}
void build(int a,int ll,int rr)
{
	l[a]=ll;
	r[a]=rr;
	mn[a]=lz[a]=inf;
	if(ll<rr)
	{
		int mid=(ll+rr)>>1;
		build(a<<1,ll,mid);
		build(a<<1|1,mid+1,rr);
	}
}
void down(int a)
{
	if(lz[a]>=inf)
		return;
	int la=a<<1,ra=a<<1|1,val=lz[a];
	mn[la]=min(mn[la],val);
	mn[ra]=min(mn[ra],val);
	lz[la]=min(lz[la],val);
	lz[ra]=min(lz[ra],val);
	lz[a]=inf;
}
void add(int a,int ll,int rr,int val)
{
	if(l[a]>rr||r[a]<ll)
		return;
	if(l[a]>=ll&&r[a]<=rr)
	{
		mn[a]=min(mn[a],val);
		lz[a]=min(lz[a],val);
		return;
	}
	down(a);
	add(a<<1,ll,rr,val);
	add(a<<1|1,ll,rr,val);
	mn[a]=min(mn[a<<1],mn[a<<1|1]);
}
int ask(int a,int ll,int rr)
{
	if(l[a]>rr||r[a]<ll)
		return inf;
	if(l[a]>=ll&&r[a]<=rr)
		return mn[a];
	down(a);
	return min(ask(a<<1,ll,rr),ask(a<<1|1,ll,rr));
}
void solve(int x)
{
	build(1,1,n+1);
	sort(q[x].begin(),q[x].end());
	int rp=n+1;
	for(int i=0;i<(int)q[x].size();i++)
	{
		node t=q[x][i];
		while(rp>t.l)
		{
			rp--;
			if(rp+mnl[x][rp]-1<=n)
				add(1,mnl[x][rp],mxl[x][rp],rp);
		}
		int nl=ask(1,t.a,t.b);
		if(nl>n)
		{
			ans[t.id]=pii(-1,-1);
			continue;
		}
		int nr=nl+max(t.a,mnl[x][nl])-1;
		if(nl>=t.l&&nr<=t.r)
			ans[t.id]=pii(nl,nr);
		else
			ans[t.id]=pii(-1,-1);
	}
}
void dbg()
{
	for(int i=1;i<=26;i++)
		for(int j=1;j<=n;j++)
			printf("i:%d j:%d mn:%d mx:%d\n",i,j,mnl[i][j],mxl[i][j]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%s",s+1);
	n=strlen(s+1);
	init();
//	dbg();
	scanf("%d",&m);
	for(int i=1,x,a,b,l,r;i<=m;i++)
	{
		scanf("%d%d%d%d%d",&x,&a,&b,&l,&r);
		node tmp(i,a,b,l,r);
		q[x].push_back(tmp);
	}
	for(int i=1;i<=26;i++)
		solve(i);
	for(int i=1;i<=m;i++)
		printf("%d %d\n",ans[i].fi,ans[i].se);
	return 0;
}