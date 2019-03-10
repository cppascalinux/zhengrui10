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
	bool operator <(const pt &p) const
	{
		return x<p.x||(x==p.x&&y<p.y);
	}
	pt operator +(pt p){return pt(x+p.x,y+p.y);}
	pt operator -(pt p){return pt(x-p.x,y-p.y);}
	ll operator *(pt p){return x*p.x+y*p.y;}
	ll operator ^(pt p){return x*p.y-y*p.x;}
};
int n;
pt p[309];
int sm[309][309];
char fg[309][309][309];
ll ans3,ans4;
ll cross(pt o,pt a,pt b)
{
	return (a-o)^(b-o);
}
int sgn(ll x)
{
	return x>0?1:(x<0?-1:0);
}
int inc(pt a,pt b,pt c,pt o)
{
	if(cross(a,b,c)<0)
		swap(b,c);
	return cross(o,a,b)>0&&cross(o,b,c)>=0&&cross(o,c,a)>=0;
}
int cal(int a,int b)
{
	pt x=p[a],y=p[b];
	if((x^y)<0)
		swap(x,y);
	int ret=0;
	for(int i=1;i<=n;i++)
		if(i!=a&&i!=b)
		{
			if(inc(pt(0,0),x,y,p[i]))
			{
				fg[a][b][i]=fg[b][a][i]=1;
				ret++;
			}
		}
	return ret;
}
void init()
{
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			sm[i][j]=sm[j][i]=cal(i,j);
}
void solve(int a,int b,int c)
{
	pt x=p[a],y=p[b],z=p[c];
	if(cross(x,y,z)<0)
	{
		swap(y,z);
		swap(b,c);
	}
	int cnt=sgn(x^y)*(sm[a][b]-fg[a][b][c])+sgn(y^z)*(sm[b][c]-fg[b][c][a])+sgn(z^x)*(sm[c][a]-fg[c][a][b]);
	// int cnt=0;
	// for(int i=1;i<=n;i++)
	// 	if(i!=a&&i!=b&&i!=c)
	// 		if(inc(x,y,z,p[i]))
	// 			cnt++;
	// printf("a:%d b:%d c:%d cnt:%d\n",a,b,c,cnt);
	ans3+=cnt*(cnt-1)/2;
	ans4+=cnt*(n-cnt-3);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b2.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&p[i].x,&p[i].y);
	// sort(p+1,p+n+1);
	// for(int i=n;i>=1;i--)
	// 	p[i]=p[i]-p[1];
	ll ans=(ll)n*(n-1)*(n-2)*(n-3)*(n-4)/24;
	// printf("ans:%lld\n",ans);
	init();
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			for(int k=j+1;k<=n;k++)
				solve(i,j,k);
	// for(int i=1;i<=n;i++)
	// 	for(int j=i+1;j<=n;j++)
	// 		printf("i:%d j:%d sm:%d\n",i,j,sm[i][j]);
	ans4/=2;
	// printf("ans:%lld ans3:%lld ans4:%lld\n",ans,ans3,ans4);
	printf("%lld",ans+ans4+2*ans3);
	return 0;
}