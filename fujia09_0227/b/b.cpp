#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
ll n;
int a,b;
int getsm(ll x,int p)
{
	int ans=0;
	while(x)
	{
		ans+=x%p;
		x/=p;
	}
	return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%lld%d%d",&n,&a,&b);
		for(ll i=n;;i++)
			if(getsm(i,a)==getsm(i,b))
			{
				printf("%lld\n",i);
				break;
			}
	}
	return 0;
}