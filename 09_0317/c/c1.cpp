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
	for(int i=1;i<=m+100;i++)
	{
		int mul=n+2-i+1,inv=i;
		for(int j=1;j<=sm;j++)
		{
			while(mul%kp[j]==0)
			{
				mul/=kp[j];
				cnt[j]++;
			}
			while(inv%kp[j]==0)
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
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c1.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m,&k);

	return 0;
}