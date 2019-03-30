#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,cnt;
int v[20009];
int p[5],c[5];
int **f;
int smx[20009],smy[20009];
int re[20009];
void init()
{
	int t=n;
	for(int i=2;i*i<=t;i++)
		if(t%i==0)
		{
			p[++cnt]=i;
			while(t%i==0)
			{
				c[cnt]++;
				t/=i;
			}
		}
	if(t>1)
	{
		p[++cnt]=t;
		c[cnt]=1;
	}
}
void solve1()
{
	int st=n/p[1];
	for(int i=1;i<=n;i++)
		re[i%st]|=v[i];
	int ans=0;
	for(int i=0;i<st;i++)
		ans+=re[i]*p[1];
	if(ans==n)
		printf("-1");
	else
		printf("%d",ans-m);
}
void solve2()
{
	int x=1,y=1;
	for(int i=1;i<=c[1];i++)
		x*=p[1];
	for(int i=1;i<=c[2];i++)
		y*=p[2];
	f=(int**)calloc(x+10,sizeof(int*));
	for(int i=0;i<=x;i++)
		f[i]=(int*)calloc(y+10,sizeof(int));
	for(int i=1;i<=n;i++)
		f[i%x][i%y]=v[i];
	int ans1=0,ans2=0;
	for(int i=0;i<x;i++)
	{
		int st=y/p[2];
		for(int j=0;j<y;j++)
			re[j%st]|=f[i][j];
		for(int j=0;j<st;j++)
			ans1+=re[j]*p[2];
		memset(re,0,sizeof(int)*st);
	}
	for(int i=0;i<y;i++)
	{
		int st=x/p[1];
		for(int j=0;j<x;j++)
			re[j%st]|=f[j][i];
		for(int j=0;j<st;j++)
			ans2+=re[j]*p[1];
		memset(re,0,sizeof(int)*st);
	}
	// printf("ans1:%d ans2:%d\n",ans1,ans2);
	int ans=min(ans1,ans2);
	if(ans==n)
		printf("-1");
	else
		printf("%d",ans-m);
	memset(re,0,sizeof(re));
	for(int i=0;i<=x;i++)
		free(f[i]);
	free(f);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1,a;i<=m;i++)
	{
		scanf("%d",&a);
		v[a]=1;
	}
	init();
	if(cnt==1)
		solve1();
	else
		solve2();
	return 0;
}