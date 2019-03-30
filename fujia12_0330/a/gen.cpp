#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
using namespace std;
int s[1009];
int main()
{
	freopen("a.in","w",stdout);
	mt19937 rnd(time(0));
	int n=20,k=100;
	printf("%d %d\n",n,k);
	for(int i=1;i<=n-14;i++)
		s[i]=i;
	shuffle(s+1,s+n+1,rnd);
	for(int i=1;i<=n;i++)
		printf("%d ",s[i]);
	return 0;
}