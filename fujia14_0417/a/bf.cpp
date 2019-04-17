#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int n;
int p[100009];
int mn[100009],mx[100009];
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("bf.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",p+i);
	int ans=1;
	for(int i=1;i<=n;i++)
	{
		mn[i]=p[i],mx[i]=p[i];
		for(int j=i+1;j<=n;j++)
		{
			mx[j]=max(mx[j-1],p[j]);
			mn[j]=min(mn[j-1],p[j]);
			if(mx[j]==p[i]&&mn[j]==p[j])
				ans=max(ans,j-i+1);
		}
	}
	printf("%d",ans);
	return 0;
}