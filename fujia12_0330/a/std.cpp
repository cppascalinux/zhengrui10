#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
#define fo(i,j,k) for(LL i=j;i<=k;i++)
#define fd(i,j,k) for(LL i=j;i>=k;i--)
using namespace std;
LL const mn=1e3+9;
LL n,K,ans,a[mn],tag[mn],b[20],c[20],d[20],e[20],f[20][20],g[6000],h[6000];
void dfs2(LL now,LL sum){
    if(now>d[0]){
        g[++g[0]]=sum;
        return;
    }
    LL tmp=0;
    fd(i,d[0],1)if(!tag[d[i]]){
        tag[d[i]]=1;
        dfs2(now+1,sum+tmp+f[now][d[i]]);
        tag[d[i]]=0;
    }else tmp++;
}
void dfs3(LL now,LL sum){
    if(now>e[0]){
        h[++h[0]]=sum;
        return;
    }
    LL tmp=0;
    fd(i,e[0],1)if(!tag[e[i]]){
        tag[e[i]]=1;
        dfs3(now+1,sum+tmp+f[now+d[0]][e[i]]);
        tag[e[i]]=0;
    }else tmp++;
}
void dfs(LL now){
    if(d[0]>=b[0]/2){
        fo(i,now,c[0])e[++e[0]]=i;
        LL tmp=0;
        fo(i,1,d[0])fo(j,1,e[0])tmp+=d[i]>e[j];
        g[0]=0;dfs2(1,tmp);
        h[0]=0;dfs3(1,0);
        sort(g+1,g+g[0]+1);
        sort(h+1,h+h[0]+1);
        LL j=g[0],k=g[0];
        fo(i,1,h[0]){
            while((j-1)&&(g[j-1]>=K-h[i]))j--;
            while(k&&(g[k]>K-h[i]))k--;
            if((j<=k)&&(g[j]==K-h[i])&&(g[k]==K-h[i]))ans+=k-j+1;
        }
        fo(i,now,c[0])e[0]--;
        return;
    }
    if(now>b[0])return;
    d[++d[0]]=now;
    dfs(now+1);
    d[0]--;
    e[++e[0]]=now;
    dfs(now+1);
    e[0]--;
}
int main(){
    freopen("a.in","r",stdin);
    freopen("std.out","w",stdout);
    scanf("%lld%lld",&n,&K);
    fo(i,1,n){
        scanf("%lld",&a[i]);
        tag[a[i]]=1;
        if(!a[i])b[++b[0]]=i;
    }
    fo(i,1,n)fo(j,i+1,n)if(a[i]&&a[j])K-=a[i]>a[j];
    fo(i,1,n)if(!tag[i])c[++c[0]]=i;
    fo(i,1,14)tag[i]=0;
    fo(i,1,b[0])fo(j,1,c[0]){
        fo(k,1,b[i]-1)if(a[k])f[i][j]+=a[k]>c[j];
        fo(k,b[i]+1,n)if(a[k])f[i][j]+=a[k]<c[j];
    }
    dfs(1);
    printf("%lld",ans);
    return 0;
}
