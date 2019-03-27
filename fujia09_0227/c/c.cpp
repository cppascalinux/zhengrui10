#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#define db double
using namespace std;
int m,n,mx,tp;
int s[20],lm[20];
int op[300009][20];
int q[300009];
db mul[300009],ans[300009];
void dfs(int st,int d,db sm)
{
	if(!d)
	{
		ans[st]+=sm*sm*q[++tp];
		return;
	}
	for(int i=0;i<s[d];i++)
	{
		int t=op[st][d]-i;
		t+=t<0?s[d]+1:1;
		dfs(st,d-1,sm*mul[t]);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&m);
		n=1;
		lm[0]=1;
		mx=0;
		for(int i=1;i<=m;i++)
		{
			scanf("%d",s+i);
			n*=s[i];
			lm[i]=lm[i-1]*s[i];
			mx=max(mx,s[i]);
		}
		// printf("n:%d\n",n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",q+i);
			for(int j=1;j<=m;j++)
				op[i][j]=((i-1)/lm[j-1])%s[j];
		}
		for(int i=1;i<=mx;i++)
			mul[i]=powl(i,1/(db)m);
		memset(ans,0,sizeof(ans));
		for(int i=1;i<=n;i++)
		{
			tp=0;
			dfs(i,m,1);
		}
		sort(ans+1,ans+n+1);
		for(int i=n;i>=max(n-99,1);i--)
			printf("%.10lf ",ans[i]/2/m);
		printf("\n");
	}
	cerr<<clock();
	return 0;
}