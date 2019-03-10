#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define db double
#define ll long long
using namespace std;
struct pt
{
	ll x,y;
	pt(){}
	pt(ll a,ll b){x=a,y=b;}
	bool operator ==(pt p){return x==p.x&&y==p.y;}
	pt operator +(pt p){return pt(x+p.x,y+p.y);}
	pt operator -(pt p){return pt(x-p.x,y-p.y);}
	ll operator *(pt p){return x*p.x+y*p.y;}
	ll operator ^(pt p){return x*p.y-y*p.x;}
};
int n;
pt p[309];
int sgn(ll x)
{
	return x>0?1:(x<0?-1:0);
}
int judge(pt p1,pt q1,pt p2,pt q2)
{
	return sgn((q2-p2)^(p1-p2))*sgn((q2-p2)^(q1-p2))<=0&&
		   sgn((q1-p1)^(p2-p1))*sgn((q1-p1)^(q2-p1))<=0;
}
int solve(int a,int b,int c)
{
	int sm=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(i!=a&&i!=b&&i!=c&&j!=a&&j!=b&&j!=c)
			{
				if(!judge(p[i],p[j],p[a],p[b])&&!judge(p[i],p[j],p[b],p[c])&&!judge(p[i],p[j],p[a],p[c]))
					sm++;
			}
	return sm;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&p[i].x,&p[i].y);
	ll ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			for(int k=j+1;k<=n;k++)
				ans+=solve(i,j,k);
	printf("%lld",ans);
	return 0;
}