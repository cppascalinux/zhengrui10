#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
using namespace std;
int v[300009];
mt19937 rnd(time(0));
int cmp(int i)
{
	return rnd()%i;
}
int main()
{
	freopen("c.in","w",stdout);
	int n=300000;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		v[i]=i;
	random_shuffle(v+1,v+n+1,cmp);
	for(int i=1;i<=n;i++)
		printf("%d ",v[i]);
	return 0;
}