#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
int n,m,k;
int pw[30][1000109];
int cb[1000109],sa[1000109],sb[1000109];
void op(int x,int &cnt,int &phi,int *p,int *c)
{
	cnt=0;
	phi=x;
	for(int i=2;i*i<=x;i++)
		if(x%i==0)
		{
			p[++cnt]=i;
			c[cnt]=0;
			phi=phi/i*(i-1);
			while(x%i==0)
			{
				x/=i;
				c[cnt]++;
			}
		}
	if(x>1)
	{
		p[++cnt]=x;
		c[cnt]=1;
		phi=phi/x*(x-1);
	}
}
int qpow(int a,int b,int p)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%p)
		if(b&1)
			ans=(ll)ans*a%p;
	return ans;
}
void geta(int p)
{
	int kp[30],cp[30],cnt[30],sm=0,phi=0;
	memset(cnt,0,sizeof(cnt));
	op(p,sm,phi,kp,cp);
	for(int i=1;i<=sm;i++)
	{
		pw[i][0]=1;
		for(int j=1;j<=m+100;j++)
			pw[i][j]=(ll)pw[i][j-1]*kp[i]%p;
	}
	cb[0]=sa[0]=1;
	// printf("sm:%d kp:%d cp:%d\n",sm,kp[1],cp[1]);
	for(int i=1;i<=m+100;i++)
	{
		int mul=n+2-i+1,inv=i;
		for(int j=1;j<=sm;j++)
		{
			while(mul&&mul%kp[j]==0)
			{
				mul/=kp[j];
				cnt[j]++;
			}
			while(inv&&inv%kp[j]==0)
			{
				inv/=kp[j];
				cnt[j]--;
			}
		}
		sa[i]=cb[i]=(ll)cb[i-1]*mul%p*qpow(inv,phi-1,p)%p;
		for(int j=1;j<=sm;j++)
			sa[i]=(ll)sa[i]*pw[j][cnt[j]]%p;
	}
}
int solven(int p)
{
	geta(p);
	int inv2=(p+1)/2;
	sb[0]=(ll)sa[1]*inv2%p;
	for(int i=1;i<=m;i++)
		sb[i]=(ll)(sa[i+1]-sb[i-1]+p)*inv2%p;
	int ans=0;
	for(int i=0;i<=m;i+=2)
		ans=(ans+sb[i])%p;
	return ans;
}
int solve2(int p)
{
	geta(p);
	int bit=0;
	while((1<<bit)<p)
		bit++;
	for(int i=m+bit+10;i>=0;i--)
		sb[i]=((ll)(p-2)*sb[i+1]+sa[i+2])%p;
	int ans=0;
	for(int i=0;i<=m;i+=2)
		ans=(ans+sb[i])%p;
	return ans;
}
int crt(int a1,int p1,int a2,int p2)
{
	int tp[30],tc[30];
	int phi1,cnt1,phi2,cnt2;
	op(p1,cnt1,phi1,tp,tc);
	op(p2,cnt2,phi2,tp,tc);
	int sm=p1*p2;
	int ans1=(ll)p2*qpow(p2,phi1-1,p1)%sm*a1%sm;
	int ans2=(ll)p1*qpow(p1,phi2-1,p2)%sm*a2%sm;
	return (ans1+ans2)%sm;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c1.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m,&k);
	n-=(n&1);
	m-=(m&1);
	int p2=1,pn=k;
	while(pn%2==0)
	{
		pn/=2;
		p2*=2;
	}
	int ans2=0,ansn=0;
	if(pn>1)
		ansn=solven(pn);
	if(p2>1)
		ans2=solve2(p2);
	printf("%d",crt(ans2,p2,ansn,pn));
	return 0;
}