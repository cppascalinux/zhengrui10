//zroj609 树树树 切比雪夫距离+boruvka+set启发式合并+并查集+vector
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<set>
#define ll long long
using namespace std;
struct pt
{
	int id,v;
	pt(){}
	pt(int a,int b){id=a,v=b;}
	bool operator <(const pt &p) const
	{
		return v<p.v;
	}
};
int n;
int x[100009],y[100009];
int f[100009];
int nid[100009];
ll ndis[100009];
set<pt> sx[100009],sy[100009],gx,gy;
vector<int> v[100009];
int fnd(int x)
{
	return x==f[x]?x:f[x]=fnd(f[x]);
}
void clr(vector<int> &v)
{
	vector<int> tv;
	tv.swap(v);
}
void uni(int a,int b)
{
	if(v[a].size()>v[b].size())
		swap(a,b);//a<b;
	f[fnd(a)]=fnd(b);

	for(int i=0;i<(int)v[a].size();i++)
		v[b].push_back(v[a][i]);
	clr(v[a]);

	set<pt>::iterator it;
	for(it=sx[a].begin();it!=sx[a].end();it++)
		sx[b].insert(*it);
	sx[a].clear();
	for(it=sy[a].begin();it!=sy[a].end();it++)
		sy[b].insert(*it);
	sy[a].clear();
}
void boruvka()
{
	for(int i=1;i<=n;i++)
	{
		f[i]=i;
		v[i].push_back(i);
		sx[i].insert(pt(i,x[i]));
		sy[i].insert(pt(i,y[i]));
		gx.insert(pt(i,x[i]));
		gy.insert(pt(i,y[i]));
	}
	int res=n-1;
	ll ans=0;
	while(res)
	{
		memset(nid,0,sizeof(nid));
		for(int i=1;i<=n;i++)
			if(fnd(i)==i)
			{
				set<pt>::iterator it;
				for(it=sx[i].begin();it!=sx[i].end();it++)
					gx.erase(*it);
				for(it=sy[i].begin();it!=sy[i].end();it++)
					gy.erase(*it);

				pt mnx,mxx,mny,mxy;
				it=gx.begin();
				mnx=*it;

				it=gx.end();
				it--;
				mxx=*it;

				it=gy.begin();
				mny=*it;

				it=gy.end();
				it--;
				mxy=*it;

				ll mxdis=-1;
				int mxid=0;
				for(int j=0;j<(int)v[i].size();j++)
				{
					int t=v[i][j];
					ll dis[5];
					int uid[5];
					dis[1]=abs(x[t]-mnx.v),dis[2]=abs(x[t]-mxx.v),dis[3]=abs(y[t]-mny.v),dis[4]=abs(y[t]-mxy.v);
					uid[1]=mnx.id,uid[2]=mxx.id,uid[3]=mny.id,uid[4]=mxy.id;
					for(int k=1;k<=4;k++)
					{
						if(dis[k]>mxdis)
						{
							mxdis=dis[k];
							mxid=uid[k];
						}
					}
				}
				nid[i]=mxid;
				ndis[i]=mxdis;

				for(it=sx[i].begin();it!=sx[i].end();it++)
					gx.insert(*it);
				for(it=sy[i].begin();it!=sy[i].end();it++)
					gy.insert(*it);
			}
		for(int i=1;i<=n;i++)
			if(nid[i])
			{
				int t=nid[i];
				if(fnd(i)==fnd(t))
					continue;
				ans+=ndis[i];
				res--;
				uni(i,t);
			}
	}
	printf("%lld",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1,a,b;i<=n;i++)
	{
		scanf("%d%d",&a,&b);
		x[i]=a+b;
		y[i]=a-b;
	}
	boruvka();
	return 0;
}