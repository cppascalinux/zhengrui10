#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
#define ll long long
using namespace std;
int tp,n;
int x[109],y[109];
ll cross(ll x1,ll y1,ll x2,ll y2,ll x3,ll y3)
{
	ll tx2=x2-x1,ty2=y2-y1;
	ll tx3=x3-x1,ty3=y3-y1;
	return tx2*ty3-ty2*tx3;
}
int judge(int p,int q)
{
	for(int i=1;i<=tp;i++)
		for(int j=i+1;j<=tp;j++)
			if(cross(p,q,x[i],y[i],x[j],y[j])==0)
				return 1;
	return 0;
}
int main()
{
	mt19937_64 rnd(time(0));
	freopen("b.in","w",stdout);
	n=50;
	int mx=1000000000;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
	{
		x[i]=rnd()%mx+1,y[i]=rnd()%mx+1;
		while(judge(x[i],y[i]))
			x[i]=rnd()%mx+1,y[i]=rnd()%mx+1;
		printf("%d %d\n",x[i],y[i]);
		tp++;
	}
	return 0;
}