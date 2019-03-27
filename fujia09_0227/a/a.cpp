#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
int n;
ll ans;
int h[4],s[4][59];
int *p[4];
int solve(int d)
{
	if(!d)
		return 1;
	if(p[2][1]==d)
		return 0;
	// if(p[3][1]&&p[3][1]!=d)
	// 	return 0;
	if(p[3][1]==d)
	{
		ans+=1LL<<(d-1);
		for(int i=1;i<=50;i++)
			p[3][i]=p[3][i+1];
		swap(p[1],p[2]);
		return solve(d-1);
	}
	else if(p[1][1]==d)
	{
		for(int i=1;i<=50;i++)
			p[1][i]=p[1][i+1];
		swap(p[2],p[3]);
		return solve(d-1);
	}
	return 0;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		n=ans=0;
		memset(s,0,sizeof(s));
		for(int i=1;i<=3;i++)
		{
			p[i]=s[i];
			scanf("%d",h+i);
			n+=h[i];
			for(int j=1;j<=h[i];j++)
				scanf("%d",s[i]+j);
		}
		// for(int i=1;i<=3;i++)
		// 	for(int j=2;j<=h[i];j++)
		// 		if(s[i][j]>s[i][j-1])
		// 		{
		// 			printf("wrong data!");
		// 			return 0;
		// 		}
		// if(t==6)
		// 	for(int i=1;i<=3;i++)
		// 	{
		// 		printf("%d ",h[i]);
		// 		for(int j=1;j<=h[i];j++)
		// 		{
		// 			printf("%d ",s[i][j]);
		// 			if(j%10==0)
		// 				printf("\n");
		// 		}
		// 		printf("\n");
		// 	}
		if(solve(n))
			printf("%lld\n",(1LL<<n)-1-ans);
		else
			printf("No\n");
	}
	return 0;
}