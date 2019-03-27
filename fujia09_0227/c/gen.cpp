#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
#include<ctime>
using namespace std;
mt19937 rnd(time(0));
int main()
{
	freopen("c.in","w",stdout);
	int t=5;
	printf("%d\n",t);
	while(t--)
	{
		int m=18,n=8192;
		printf("%d\n",m);
		for(int i=1;i<=13;i++)
			printf("2 ");
		for(int j=14;j<=18;j++)
			printf("1 ");
		printf("\n");
		for(int i=1;i<=n;i++)
			printf("%d ",rnd()%100000+1);
		printf("\n");
	}
	return 0;
}