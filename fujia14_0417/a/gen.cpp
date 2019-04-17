#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
using namespace std;
int s[100009];
int main()
{
	freopen("a.in","w",stdout);
	mt19937 rnd(time(0)+clock());
	int n=100000;
	for(int i=1;i<=n;i++)
		s[i]=i;
	shuffle(s+1,s+n+1,rnd);
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d ",s[i]);
	return 0;
}