#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,n) for (int i=0;i<n;i++)
#define For(i,n) for (int i=1;i<=n;i++)
#define FOR(i,a,b) for (int i=a;i<=b;i++)
const int N=30;
int n,sz,ans,x[N],y[N],a[1000000][4],v[N];
inline bool same(int i,int j)
{
    return x[i]==x[j] && y[i]==y[j];
}
void dfs(int x)
{
    if (x>ans) ans=x;
    bool flag;
    For(i,sz)
    {
        flag=1;
        rep(k,4) if (!v[a[i][k]]) {flag=0;break;}
        if (flag)
        {
            rep(k,4) v[a[i][k]]--;
            dfs(x+1);
            rep(k,4) v[a[i][k]]++;
        }
    }
}
int main()
{
    while(1)
    {
        scanf("%d",&n);
        if (n==-1) return 0;
        sz=0;
        For(i,n) 
        {
            scanf("%d%d",&x[i],&y[i]);
            bool flag=0;
            For(j,sz) 
                if (same(i,j)) {v[j]++;flag=1;break;}
            if (!flag) x[++sz]=x[i],y[sz]=y[i],v[sz]=1;
        }
        n=sz;sz=0;
        
        For(i,n)
            For(j,n)
            {
                if (same(i,j)) continue;
                For(k,n)
                {
                    if (same(i,k) || same(j,k) || x[k]!=x[i] || y[k]!=y[j]) continue;
                    For(l,n)
                    {
                        if (same(i,l) || same(j,l) || same(k,l) || x[l]!=x[j] || y[l]!=y[i]) continue;
                        if (x[l]-x[i]!=y[k]-y[i]) continue;
                        a[++sz][0]=i;
                        a[sz][1]=j;
                        a[sz][2]=k;
                        a[sz][3]=l;
                    }
                }        
            }
        ans=0;
        dfs(0);
        printf("%d\n",ans*4);
    }
}
