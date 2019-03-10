#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#define ll long long
using namespace std;
int n,tp,q;
char s[1009];
struct node
{
	char ss[109];
	bool operator <(const node &p) const
	{
		return strcmp(ss+1,p.ss+1)<0;
	}
};
node t[100009];
char ans[100000009];
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("bf.out","w",stdout);
#endif
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		s[i]-='a'-1;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
		{
			tp++;
			for(int k=i;k<=j;k++)
				t[tp].ss[k-i+1]=s[k];
		}
	sort(t+1,t+tp+1);
	// for(int i=1;i<=tp;i++)
	// {
	// 	printf("i:%d ",i);
	// 	for(int j=1;t[i].ss[j];j++)
	// 		printf("%c",t[i].ss[j]+'a'-1);
	// 	printf("\n");
	// }
	int lst=0;
	for(int i=1;i<=tp;i++)
		for(int j=1;t[i].ss[j];j++)
		{
			ans[++lst]=t[i].ss[j];
		}
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		ll p;
		scanf("%lld",&p);
		printf("%c",ans[p]+'a'-1);
	}
	return 0;
}