#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#define ll long long
#define inf 200000000000000000LL
using namespace std;
struct node
{
	int sm;
	ll x;
	node(){}
	node(int a,ll b){sm=a,x=b;}
	bool operator <(const node &p) const
	{
		return x>p.x;
	}
};
ll n;
int b1,b2;
ll nxt(ll x,int bs,int sm)//>=x,base=bs,f=sm
{
	int cnt=-1,p[70],np[70],mx;
	ll pw[70];
	ll t=x;
	memset(p,0,sizeof(p));
	int tmpsm=0;
	while(t)
	{
		p[++cnt]=t%bs;
		tmpsm+=p[cnt];
		t/=bs;
	}
	if(tmpsm==sm)
		return x;
	pw[0]=1;
	for(int i=1;;i++)
	{
		pw[i]=pw[i-1]*bs;
		mx=i;
		if(pw[i]*(bs-1)>min((ll)n*10,inf))
			break;
	}
	for(int i=mx;i>=0;i--)
	{
		for(int j=p[i];j<bs;j++)
		{
			if(i*(bs-1)<sm-j)
				continue;
			if(j==p[i])
			{
				int tsm=sm-j;
				for(int k=mx;k>=i;k--)
					np[k]=p[k];
				for(int k=i-1;k>=0;k--)
				{
					np[k]=min(bs-1,tsm);
					tsm-=np[k];
				}
				ll nx=0;
				for(int k=0;k<=mx;k++)
					nx+=np[k]*pw[k];
				if(nx>=x)
				{
					sm-=j;
					break;
				}
			}
			else
			{
				sm-=j;
				for(int k=mx;k>=i+1;k--)
					np[k]=p[k];
				np[i]=j;
				for(int k=0;k<=i-1;k++)
				{
					np[k]=min(bs-1,sm);
					sm-=np[k];
				}
				ll nx=0;
				for(int k=0;k<=mx;k++)
					nx+=np[k]*pw[k];
				return nx;
			}
		}
	}
	return inf;
}
void dbg()
{
	ll n;
	int bs,sm;
	while(1)
	{
		scanf("%lld %d %d",&n,&bs,&sm);
		printf("%lld\n",nxt(n,bs,sm));
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	int t;
	// dbg();
	scanf("%d",&t);
	while(t--)
	{
		scanf("%lld%d%d",&n,&b1,&b2);
		priority_queue<node> pq;
		for(int i=1;i<=400;i++)
			pq.push(node(i,n));
		for(;;)
		{
			node t=pq.top();
			pq.pop();
			ll na=nxt(t.x,b1,t.sm);
			ll nb=nxt(t.x,b2,t.sm);
			ll mx=max(na,nb);
			if(mx==t.x)
			{
				printf("%lld\n",mx);
				break;
			}
			pq.push(node(t.sm,mx));
		}
	}
	return 0;
}