//2019.04.17
//zroj644 B. 道路修建 最小割建模+网络流
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#define db long double
#define eps 1e-8
#define inf 0x7F7F7F7F
using namespace std;
int n,m,tot=1,st,ed;
int t[69];
int w[69][69];
int hd[4009],eg[10000009],nxt[10000009],cap[10000009];
int dep[4009],cur[4009];
int dis0[69];
void bfs0()
{
	queue<int> q;
	q.push(1);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=2;i<=n;i++)
			if(!dis0[i]&&w[x][i])
			{
				dis0[i]=dis0[x]+1;
				q.push(i);
			}
	}
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
	// memset(dep+1,0,ed<<2);
	memset(dep,0,sizeof(dep));
	dep[st]=1;
	queue<int> q;
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
	int totf=0;
	while(bfs())
	{
		// printf("noasfhnoiasfoas");
		for(int i=1;i<=ed;i++)
			cur[i]=hd[i];
		totf+=dfs(st,inf);
	}
	return totf;
}
int cal(int r,int c)
{
	return (r-1)*(n+1)+c+1;
}
int getv(int a,int b)
{
	return (int)(10*logl(233*(a-b)*(a-b)+1));
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b2.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	if(!n)
	{
		printf("1061109567");
		return 0;
	}
	for(int i=1;i<=n;i++)
		scanf("%d",t+i);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		w[a][b]=w[b][a]=1;
	}
	if(n==1)
	{
		printf("%d",getv(0,t[1]));
		return 0;
	}
	bfs0();
	st=n*(n+1)+1,ed=n*(n+1)+2;
	// printf("st:%d ed:%d\n",st,ed);
	ins(st,cal(1,0),inf);
	ins(cal(1,0),cal(1,1),getv(0,t[1]));
	for(int j=1;j<=n-1;j++)
		ins(cal(1,j),cal(1,j+1),inf);
	ins(cal(1,n),ed,inf);
	for(int i=2;i<=n;i++)
	{
		ins(st,cal(i,0),inf);
		// printf("i:%d v:%d\n",i,getv(t[i],0));
		ins(cal(i,0),cal(i,1),inf);
		for(int j=1;j<=n-1;j++)
			ins(cal(i,j),cal(i,j+1),getv(t[i],j));
		ins(cal(i,n),ed,inf);
	}
	for(int a=1;a<=n;a++)
		for(int b=a+1;b<=n;b++)
			if(w[a][b])
				for(int j=0;j<=n-1;j++)
					ins(cal(a,j+1),cal(b,j),inf),ins(cal(b,j+1),cal(a,j),inf);
	printf("%d",flow());
	return 0;
}