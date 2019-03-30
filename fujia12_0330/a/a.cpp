#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define ll long long
using namespace std;
int n,k,tpl,tpr,cntl,cntr,tp0,tp1;
int s[1009],eptp[19],eptv[19];
int sn[1009];
int used[1009];
int f[1009][1009];
int sl[10009],sr[10009];
int st[19],vis[19],g[19];
int buc[10000009];
void init()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			f[i][j]=f[i-1][j]+(s[i]>0&&s[i]<=j);
	int sm=0;
	for(int i=1;i<=n;i++)
		sn[i]=sn[i-1]+(s[i]>0);
	for(int i=1;i<=n;i++)
		if(s[i])
			sm+=(sn[i]-1-f[i][s[i]-1]);
	// printf("sm:%d\n",sm);
	k-=sm;
}
void cal(int rev,int s,int c)
{
	int sm=rev,mx=0;
	for(int i=1;i<=tp0;i++)
		if(s&(1<<(i-1)))
			g[++mx]=i;
	// printf("rev:%d+++++++++\n",rev);
	// for(int i=1;i<=mx;i++)
	// 	printf("%d ",st[i]);
	// printf("\n");
	for(int i=1;i<=mx;i++)
	{
		int pos,val=eptv[g[st[i]]];
		if(c==0)
			pos=eptp[i];
		else
			pos=eptp[i+tpl];
		// printf("pos:%d val:%d\n",pos,val);
		sm+=sn[pos]-f[pos][val];
		// printf("sm1:%d\n",sm);
		sm+=used[val]-f[pos][val];
		// printf("sm2:%d\n",sm);
	}
	if(c==0)
		sl[++cntl]=sm;
	else
		sr[++cntr]=sm;
}
void dfs(int d,int mx,int rev,int s,int c)
{
	if(d>mx)
	{
		cal(rev,s,c);
		return;
	}
	int sm=0;
	for(int i=1;i<=mx;i++)
	{
		if(vis[i])
			sm++;
		else
		{
			vis[i]=1;
			st[d]=i;
			dfs(d+1,mx,rev+d-1-sm,s,c);
			vis[i]=0;
		}
	}
}
ll solve(int s)
{
	cntl=cntr=0;
	dfs(1,tpl,0,s,0);
	dfs(1,tpr,0,((1<<tp0)-1)^s,1);
	// for(int i=tp0;i>=1;i--)
	// 	if(s&(1<<(i-1)))
	// 		printf("1");
	// 	else
	// 		printf("0");
	// printf("----------------\n");
	// for(int i=1;i<=cntl;i++)
	// 	printf("%d ",sl[i]);
	// printf("\n");
	// for(int i=1;i<=cntr;i++)
	// 	printf("%d ",sr[i]);
	// printf("\n");
	int tsm=0;
	int tk=0;
	for(int i=1;i<=tp0;i++)
		if(!(s&(1<<(i-1))))
			tsm++;
		else
			tk+=tsm;
	tk=k-tk;
	for(int i=1;i<=cntr;i++)
		buc[sr[i]]++;
	ll ans=0;
	for(int i=1;i<=cntl;i++)
		if(tk-sl[i]>=0)
			ans+=buc[tk-sl[i]];
	for(int i=1;i<=cntr;i++)
		buc[sr[i]]--;
	return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",s+i);
		if(s[i])
			used[s[i]]=1;
	}
	init();
	if(k<0)
	{
		printf("0");
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		if(!s[i])
			eptp[++tp0]=i;
		if(!used[i])
			eptv[++tp1]=i;
	}
	for(int i=1;i<=n;i++)
		used[i]+=used[i-1];
	tpl=tp0>>1;
	tpr=tp0-tpl;
	// printf("tp0:%d\n",tp0);
	ll ans=0;
	for(int i=0;i<1<<tp0;i++)
	{
		int sm=0;
		for(int j=1;j<=tp0;j++)
			if(i&(1<<(j-1)))
				sm++;
		if(sm==tpl)
			ans+=solve(i);
	}
	printf("%lld",ans);
	return 0;
}
