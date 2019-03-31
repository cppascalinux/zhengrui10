//zroj641 叶片 二分图最大权独立集 dinic
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define inf 0x7F7F7F7F
using namespace std;
int n,m,cnt,tot=1,st,ed,sme;
int p[20],k[20];
int v[20009];
int res[20009];
int hd[50009],eg[1000009],nxt[1000009],cap[1000009];
int cur[50009],dep[50009];
void init()
{
	int t=n;
	for(int i=2;i*i<=t;i++)
		if(t%i==0)
		{
			p[++cnt]=i;
			while(t%i==0)
			{
				t/=i;
				k[cnt]++;
			}
		}
	if(t>1)
	{
		p[++cnt]=t;
		k[cnt]=1;
	}
}
void solve1()
{
	int x=n/p[1];
	for(int i=1;i<=n;i++)
		res[i%x]|=v[i];
	int ans=0;
	for(int i=0;i<x;i++)
		ans+=res[i]*p[1];
	if(ans==n)
		printf("-1");
	else
		printf("%d",ans-m);
}
void ins(int a,int b,int c)
{
	eg[++tot]=b;
	cap[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
	
	eg[++tot]=a;
	cap[tot]=0;
	nxt[tot]=hd[b];
	hd[b]=tot;
}
int bfs()
{
	queue<int> q;
	memset(dep,0,sizeof(dep));
	dep[st]=1;
	q.push(st);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=hd[x];i;i=nxt[i])
			if(cap[i]&&!dep[eg[i]])
			{
				dep[eg[i]]=dep[x]+1;
				q.push(eg[i]);
			}
	}
	return dep[ed];
}
int dfs(int x,int a)
{
	if(x==ed||!a)
		return a;
	int f,totf=0;
	for(int &i=cur[x];i;i=nxt[i])
		if(cap[i]&&dep[eg[i]]==dep[x]+1&&(f=dfs(eg[i],min(a,cap[i]))))
		{
			cap[i]-=f;
			cap[i^1]+=f;
			a-=f;
			totf+=f;
			if(!a)
				break;
		}
	return totf;
}
int flow()
{
	int x=n/p[1],y=n/p[2];
	int totf=0;
	while(bfs())
	{
		for(int i=1;i<=x+y+2;i++)
			cur[i]=hd[i];
		totf+=dfs(st,inf);
	}
	return totf;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1,a;i<=m;i++)
	{
		scanf("%d",&a);
		v[a]=1;
	}
	if(n==1)
	{
		printf("-1");
		return 0;
	}
	init();
	if(cnt==1)
	{
		solve1();
		return 0;
	}
	int x=n/p[1],y=n/p[2];
	st=x+y+1,ed=x+y+2;
	for(int i=1;i<=n;i++)
		res[i%x]|=v[i];
	for(int i=0;i<x;i++)
		if(!res[i])
		{
			ins(st,i+1,p[1]);
			sme+=p[1];
		}

	memset(res,0,sizeof(res));
	for(int i=1;i<=n;i++)
		res[i%y]|=v[i];
	for(int i=0;i<y;i++)
		if(!res[i])
		{
			ins(i+x+1,ed,p[2]);
			sme+=p[2];
		}
	for(int i=1;i<=n;i++)
	{
		int tx=i%x,ty=i%y;
		ins(tx+1,ty+x+1,inf);
	}
	int ans=sme-flow();
	if(!ans)
		printf("-1");
	else
		printf("%d",n-m-ans);
	return 0;
}