#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
using namespace std;
int main()
{
	freopen("c.in","w",stdout);
	int mul=1;
	for(int i=1;i<=1000000;i++)
		mul*=i;
	cerr<<mul;
	mt19937 rnd(time(0)+clock());
	int n=50000,m=25000;
	printf("%d %d\n",n,m);
	for(int i=2;i<=n;i++)
		printf("%d %d %d\n",i,rnd()%(i-1)+1,rnd()%10000+1);
	return 0;
}