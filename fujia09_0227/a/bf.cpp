#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,sm;
int v[4][21];
int ans[1050009][4][21];
void solve(int d,int l1,int l2,int l3)
{
	if(!d)
		return;
	solve(d-1,l1,l3,l2);
	sm++;
	for(int i=1;i<=3;i++)
		for(int j=1;j<=n;j++)
			ans[sm][i][j]=ans[sm-1][i][j];
	for(int i=n;i>=1;i--)
		if(ans[sm][l1][i])
		{
			ans[sm][l1][i]=0;
			for(int j=1;j<=n;j++)
				if(!ans[sm][l3][j])
				{
					ans[sm][l3][j]=d;
					break;
				}
			break;
		}
	solve(d-1,l2,l1,l3);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("bf.out","w",stdout);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		n=0;
		memset(v,0,sizeof(v));
		for(int i=1;i<=3;i++)
		{
			int a;
			scanf("%d",&a);
			n+=a;
			for(int j=1;j<=a;j++)
				scanf("%d",v[i]+j);
		}
		memset(ans,0,sizeof(ans));
		for(int i=1;i<=n;i++)
			ans[0][1][i]=n-i+1;
		sm=0;
		solve(n,1,2,3);
		int out=-1;
		for(int i=0;i<=sm;i++)
		{
			int fg=1;
			for(int j=1;j<=3;j++)
				for(int k=1;k<=n;k++)
					if(v[j][k]!=ans[i][j][k])
					{
						fg=0;
						break;
					}
			if(fg)
			{
				out=sm-i;
				break;
			}
		}
		if(out==-1)
			printf("No\n");
		else
			printf("%d\n",out);
		// for(int i=0;i<=2;i++)
		// {
		// 	printf("i:%d-------------------\n",i);
		// 	for(int j=1;j<=3;j++)
		// 	{
		// 		printf("j:%d ",j);
		// 		for(int k=1;k<=n;k++)
		// 			if(ans[i][j][k])
		// 				printf("%d ",ans[i][j][k]);
		// 		printf("\n");
		// 	}
		// 	printf("\n");
		// }
	}
	return 0;
}