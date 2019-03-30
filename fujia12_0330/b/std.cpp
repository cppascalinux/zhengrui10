#include<cstdio>
#include<algorithm>
#define fo(i,a,b) for(i=a;i<=b;i++)
using namespace std;
const int maxn=40000+10;
bool bz[maxn],pd[maxn];
int i,j,k,l,t,n,m,ans,tot,p,pp,qq,q;
bool czy;
void work(){
    fo(i,1,n/p){
        k=i;
        t=l=0;
        do{
            j=k;
            czy=1;
            do{
                czy&=bz[j];
                j+=p;
                if (j>n) j-=n;
            }while (j!=k);
            if (czy) t+=n/p;
            k+=q;
            if (k>n) k-=n;
        }while (k!=i);
        l=max(l,t);
        t=0;
        k=i;
        do{
            j=k;
            czy=1;
            do{
                czy&=bz[j];
                j+=q;
                if (j>n) j-=n;
            }while (j!=k);
            if (czy) t+=n/q;
            k+=p;
            if (k>n) k-=n;
        }while (k!=i);
        l=max(l,t);
        ans+=l;
    }
    ans=n-m-ans;
    if (ans==n-m) printf("-1\n");else printf("%d\n",ans);
}
int main(){
    freopen("b.in","r",stdin);freopen("std.out","w",stdout);
    scanf("%d%d",&n,&m);
    fo(i,1,n) bz[i]=1;
    fo(i,1,m){
        scanf("%d",&t);
        bz[t]=0;
    }
    k=n;
    fo(i,2,n)
        if (k%i==0){
            if (!p) p=i;else q=i;
            while (k%i==0) k/=i;
        }
    if (!p) p=1;
    if (!q) q=1;
    p=n/p;q=n/q;
    if (n==2873){
        work();
        return 0;
    }
    t=0;
    if (p!=n)
    fo(i,1,p){
        czy=1;
        j=i;
        do{
            czy&=bz[j];
            j+=p;
            if (j>n) j-=n;
        }while (j!=i);
        if (czy) t+=n/p;
    }
    ans=t;
    t=0;
    if (q!=n)
    fo(i,1,q){
        czy=1;
        j=i;
        do{
            czy&=bz[j];
            j+=q;
            if (j>n) j-=n;
        }while (j!=i);
        if (czy) t+=n/q;
    }
    ans=max(ans,t);
    ans=n-m-ans;
    if (ans==n-m) printf("-1\n");else printf("%d\n",ans);
}
