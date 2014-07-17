#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,n) for (int i=0;i<n;i++)
#define For(i,n) for (int i=1;i<=n;i++)
#define FOR(i,a,b) for (int i=a;i<=b;i++)
using namespace std;
const int N=1010,M=2000010;
int sz,top,tot,timee,ans,n,m,block,u,v,w,
    cr[N],sk[N],dfn[N],low[N],en[N],pre[M],g[M],value[M];
void Ins(int u,int v,int w)
{
    pre[++sz]=en[u];en[u]=sz;g[sz]=v;value[sz]=w;
}
void Popto(int x)
{
    tot++;
    for(;sk[top+1]!=x;top--)
        cr[sk[top]]=tot;
}
void Tarjan(int x,int way)
    {
        dfn[x]=low[x]=++timee;
        sk[++top]=x;
        for(int i=en[x];i;i=pre[i])
        {
            int v=g[i];
            if (!dfn[v])
            {
                Tarjan(v,i^1);
                low[x]=min(low[x],low[v]);
            }
            else if (i!=way) low[x]=min(low[x],dfn[v]);
        }
        if (low[x]==dfn[x]) {Popto(x);if (value[way]<ans) ans=value[way];}
    }
int bcc()
{
    block=0;
    For(i,n) if(!dfn[i]) 
    {
        Tarjan(i,0);
        block++;
    }
    return tot;
}
int main()
{
    value[0]=100000;
    while(1)
    {
        sz=1;ans=100000,timee=tot=0;
        memset(en,0,sizeof(en));
        memset(dfn,0,sizeof(dfn));
        
        scanf("%d%d",&n,&m);
        if (n+m==0) return 0;
        For (i,m)
        {
            scanf("%d%d%d",&u,&v,&w);
            Ins(u,v,w);Ins(v,u,w);
        }
        bcc();
        if (ans>10000) ans=-1;
        if (ans==0) ans=1;
        //printf("%d %d %d %d\n",tot,sz,block,ans);
        if (block>1)  printf("0\n");
                 else printf("%d\n",ans);
    }
}
