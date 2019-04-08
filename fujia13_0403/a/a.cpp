//2019.04.08
//zroj169【18 省选 10】Barbecue 分治+dfs
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,tot;
int hd[300009],eg[600009],nxt[600009];
void rd(int &x)
{
	char c=0;
	x=0;
	while(c<'0'||c>'9')
		c=gc();
	while(c>='0'&&c<='9')
		x=x*10+(c&15),c=gc();
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		
	}
	return 0;
}