#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,q,tp;
char s[5009];
pii ans[15000009];
ll sm[15000009];
int sa[5009],rk[5009],h[5009],t1[5009],t2[5009],c[5009];
int st[5009];
void getsa()
{
	int *x=t1,*y=t2,m=26;
	memset(c,0,(m+1)<<2);
	for(int i=1;i<=n;i++)
		c[x[i]=s[i]]++;
	for(int i=1;i<=m;i++)
		c[i]+=c[i-1];
	for(int i=1;i<=n;i++)
		sa[c[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int p=0;
		for(int i=n-k+1;i<=n;i++)
			y[++p]=i;
		for(int i=1;i<=n;i++)
			if(sa[i]>=k+1)
				y[++p]=sa[i]-k;
		memset(c,0,(m+1)<<2);
		for(int i=1;i<=n;i++)
			c[x[i]]++;
		for(int i=1;i<=m;i++)
			c[i]+=c[i-1];
		for(int i=n;i>=1;i--)
			sa[c[x[y[i]]]--]=y[i];
		p=0;
		for(int i=1;i<=n;i++)
			y[sa[i]]=x[sa[i]]==x[sa[i-1]]&&x[sa[i]+k]==x[sa[i-1]+k]?p:++p;
		swap(x,y);
		m=p;
		if(m>=n)
			break;
	}
}
void geth()
{
	for(int i=1;i<=n;i++)
		rk[sa[i]]=i;
	int k=0;
	for(int i=1;i<=n;i++)
	{
		if(k)
			k--;
		int p=sa[rk[i]-1];
		while(s[i+k]==s[p+k])
			k++;
		h[rk[i]]=k;
	}
	for(int i=1;i<=n;i++)
		st[i]=sa[i];
}
void dbg()
{
	for(int i=1;i<=n;i++)
		printf("i:%d sa:%d h:%d\n",i,sa[i],h[i]);
}
void getans()
{
	for(int i=1;i<=n;i++)
	{
		int p=sa[i];
		for(int j=st[i];j<=n;j++)
		{
			ans[++tp]=pii(p,j);
			int l=j-p+1;
			for(int k=i+1;k<=n;k++)
			{
				if(h[k]<l)
					break;
				ans[++tp]=pii(sa[k],sa[k]+l-1);
				st[k]=sa[k]+l;
			}
		}
	}
	for(int i=1;i<=tp;i++)
		sm[i]=sm[i-1]+ans[i].se-ans[i].fi+1;
	// printf("tp;%d\n",tp);
	// for(int i=1;i<=tp;i++)
	// 	printf("i:%d fi;%d se:%d\n",i,ans[i].fi,ans[i].se);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		s[i]-='a'-1;
	getsa();
	geth();
	// dbg();
	getans();
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		ll a;
		scanf("%lld",&a);
		int p=lower_bound(sm+1,sm+tp+1,a)-sm-1;
		int res=a-sm[p];
		printf("%c",s[ans[p+1].fi+res-1]+'a'-1);
	}
	return 0;
}