//zroj642 树 点分树+二分答案
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
int n,m,tot,mn,rt;
int hd[50009],eg[100009],nxt[100009],len[100009];
int vis[50009],sz[50009],f[50009];
vector<int> dis[50009],sub[50009];
vector<pii> nm[50009];
void ins(int a,int b,int c)
{
	eg[++tot]=b;
	len[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void getrt(int x,int fa,int siz)
{
	sz[x]=1;
	int mx=0;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa&&!vis[eg[i]])
		{
			getrt(eg[i],x,siz);
			sz[x]+=sz[eg[i]];
			mx=max(mx,sz[eg[i]]);
		}
	mx=max(mx,siz-sz[x]);
	if(mx<mn)
	{
		mn=mx;
		rt=x;
	}
}
void dfs(int x,int fa,int sm,int frm,int prt)
{
	sub[frm].push_back(sm);
	dis[prt].push_back(sm);
	nm[prt].push_back(pii(x,sm));
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa&&!vis[eg[i]])
			dfs(eg[i],x,sm+len[i],frm,prt);
}
void solve(int x,int siz)
{
	// printf("x:%d\n",x);
	vis[x]=1;
	dis[x].push_back(0);
	nm[x].push_back(pii(x,0));
	for(int i=hd[x];i;i=nxt[i])
		if(!vis[eg[i]])
		{
			int nsz=sz[eg[i]]>sz[x]?siz-sz[x]:sz[eg[i]];
			mn=inf;
			getrt(eg[i],0,nsz);
			f[rt]=x;
			dfs(eg[i],0,len[i],rt,x);
			sort(sub[rt].begin(),sub[rt].end());
			solve(rt,nsz);
		}
	sort(dis[x].begin(),dis[x].end());
	sort(nm[x].begin(),nm[x].end());
}
int cal(int x,int val)
{
	int ans=0;
	for(int lst=0,now=x;now;lst=now,now=f[now])
	{
		int disx=lower_bound(nm[now].begin(),nm[now].end(),pii(x,-1))->se;
		int sm=val-disx;
		ans+=lower_bound(dis[now].begin(),dis[now].end(),sm)-dis[now].begin();
		ans-=lower_bound(sub[lst].begin(),sub[lst].end(),sm)-sub[lst].begin();
	}
	// printf("x:%d val:%d ans:%d\n",x,val,ans+1);
	return ans+1;
}
int bin(int x)
{
	int l=0,r=500000000,mid;
	while(l<r)
	{
		mid=(l+r+1)>>1;
		if(cal(x,mid)<=m)
			l=mid;
		else
			r=mid-1;
	}
	return l;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c1.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	m++;
	for(int i=1,a,b,c;i<=n-1;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		ins(a,b,c);
		ins(b,a,c);
	}
	mn=inf;
	getrt(1,0,n);
	solve(rt,n);
	// for(int i=1;i<=n;i++)
	// {
	// 	printf("i:%d f:%d---------------\ndis: ",i,f[i]);
	// 	for(int j=0;j<(int)dis[i].size();j++)
	// 		printf("%d ",dis[i][j]);
	// 	printf("\nsub: ");
	// 	for(int j=0;j<(int)sub[i].size();j++)
	// 		printf("%d ",sub[i][j]);
	// 	printf("\n");
	// 	for(int j=0;j<(int)nm[i].size();j++)
	// 		printf("fi:%d se:%d\n",nm[i][j].fi,nm[i][j].se);
	// }
	for(int i=1;i<=n;i++)
		printf("%d\n",bin(i));
	return 0;
}