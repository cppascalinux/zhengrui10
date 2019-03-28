#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
#include<ctime>
using namespace std;
int main()
{
	freopen("a.in","w",stdout);
	mt19937 rnd(time(0));
	int t=5;
	printf("%d\n",t);
	while(t--)
	{
		int n=50000,k=100;
		printf("%d %d\n",n,k);
		for(int i=1;i<=n;i++)
			printf("%d",rnd()%10);
		printf("\n");
	}
	return 0;
}