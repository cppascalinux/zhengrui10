#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
#include<ctime>
using namespace std;
int s[25];
mt19937 rnd(time(0));
bool cmp(int a,int b)
{
	return a>b;
}
int main()
{
	srand(time(0));
	freopen("a.in","w",stdout);
	int t=5;
	printf("%d\n",t);
	while(t--)
	{
		int n=5;
		for(int i=1;i<=n;i++)
			s[i]=i;
		random_shuffle(s+1,s+n+1);
		int t1=rnd()%n+1;
		int t2=rnd()%n+1;
		if(t1>t2)
			swap(t1,t2);
		sort(s+1,s+t1+1,cmp);
		sort(s+t1+1,s+t2+1,cmp);
		sort(s+t2+1,s+n+1,cmp);
		printf("%d ",t1);
		for(int i=1;i<=t1;i++)
			printf("%d ",s[i]);
		printf("\n%d ",t2-t1);
		for(int i=t1+1;i<=t2;i++)
			printf("%d ",s[i]);
		printf("\n%d ",n-t2);
		for(int i=t2+1;i<=n;i++)
			printf("%d ",s[i]);
		printf("\n");
	}
	return 0;
}