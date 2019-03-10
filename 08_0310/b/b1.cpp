#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
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
ll cross(pt &o,pt &a,pt &b)
{
	return (a-o)^(b-o);
}
int sgn(ll x)
{
	return x>0?1:(x<0?-1:0);
}
// int judge(pt p1,pt q1,pt p2,pt q2)
// {
// 	return sgn((q2-p2)^(p1-p2))*sgn((q2-p2)^(q1-p2))<=0&&
// 		   sgn((q1-p1)^(p2-p1))*sgn((q1-p1)^(q2-p1))<=0;
// }
int judge(pt p1,pt q1,pt p2,pt q2)
{
	return sgn(cross(p2,q2,p1))*sgn(cross(p2,q2,q1))<=0&&
		   sgn(cross(p1,q1,p2))*sgn(cross(p1,q1,q2))<=0;
}
int solve1(int a,int b,int c)
{
	pt x=p[a],y=p[b],z=p[c];
	if(cross(x,y,z)<0)
		swap(y,z);
	int sm=0;
	for(int i=1;i<=n;i++)
		if(i!=a&&i!=b&&i!=c)
		{
			pt t=p[i];
			if(cross(t,x,y)>0&&cross(t,y,z)>0&&cross(t,z,x)>0)
				sm++;
		}
	return sm*(sm-1)/2+(n-sm-3)*(n-sm-4)/2;
}
int solve2(int o,int a,int b)
{
	pt u=p[o],x=p[a],y=p[b];
	if(cross(u,x,y)<0)
		swap(x,y);
	int sm=0;
	for(int i=1;i<=n;i++)
		if(i!=o&&i!=a&&i!=b)
		{
			pt t=p[i];
			if(judge(u,t,x,y))
				sm++;
		}
	return sm*(sm-1)/2;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&p[i].x,&p[i].y);
	ll ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			for(int k=j+1;k<=n;k++)
				ans+=solve1(i,j,k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=j+1;k<=n;k++)
				if(i!=j&&i!=k)
					ans-=solve2(i,j,k);
	printf("%lld",ans);
	return 0;
}