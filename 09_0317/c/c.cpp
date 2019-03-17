#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,k;
int cb[5009][5009];
void solve()
{
	for(int i=0;i<=n;i++)
		cb[i][i]=cb[i][0]=1;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=i-1;j++)
			cb[i][j]=(cb[i-1][j]+cb[i-1][j-1])%k;
	int ans=0;
	for(int i=0;i<=n;i+=2)
		for(int j=0;j<=m;j+=2)
			ans=(ans+cb[i][j])%k;
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=i;j++)
			printf("%d ",cb[i][j]);
		printf("\n");
	}
	printf("%d",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m,&k);
	solve();
	return 0;
}