#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
#define ll long long
using namespace std;
int main()
{
	mt19937 rnd(time(0));
	mt19937_64 rnd64(time(0));
	freopen("a.in","w",stdout);
	int n=5000,q=5000;
	for(int i=1;i<=n;i++)
		printf("%c",rnd()%2+'a');
	ll mx=(ll)n*(n+1)*(n+2)/6;
	printf("\n%d\n",q);
	for(int i=1;i<=q;i++)
		printf("%lld ",rnd64()%mx+1);
	return 0;
}