//zroj609 树树树 切比雪夫距离+贪心+kruskal
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define inf 0x7FFFFFFF
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n;
int f[100009];
pii p[100009];
pii e[400009];
int fnd(int x)
{
	return x==f[x]?x:f[x]=fnd(f[x]);
}
ll dis(pii a,pii b)
{
	return max(abs(a.fi-b.fi),abs(a.se-b.se));
}
bool cmp(pii a,pii b)
{
	return dis(p[a.fi],p[a.se])>dis(p[b.fi],p[b.se]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c1.out","w",stdout);
#endif
	scanf("%d",&n);
	int lx=1,rx=1,ly=1,ry=1;
	for(int i=1,a,b;i<=n;i++)
	{
		scanf("%d%d",&a,&b);
		p[i]=pii(a+b,a-b);
		if(p[i].fi<p[lx].fi)
			lx=i;
		if(p[i].fi>p[rx].fi)
			rx=i;
		if(p[i].se<p[ly].se)
			ly=i;
		if(p[i].se>p[ry].se)
			ry=i;
	}
	// printf("lx:%d rx:%d ly:%d ry:%d\n",lx,rx,ly,ry);
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		e[++cnt]=pii(i,lx);
		e[++cnt]=pii(i,rx);
		e[++cnt]=pii(i,ly);
		e[++cnt]=pii(i,ry);
	}
	sort(e+1,e+cnt+1,cmp);
	for(int i=1;i<=n;i++)
		f[i]=i;
	ll ans=0;
	for(int i=1;i<=cnt;i++)
	{
		int fx=fnd(e[i].fi),fy=fnd(e[i].se);
		if(fx==fy)
			continue;
		f[fx]=fy;
		// printf("fi;%d se:%d\n",e[i].fi,e[i].se);
		ans+=dis(p[e[i].fi],p[e[i].se]);
	}
	printf("%lld",ans);
	return 0;
}