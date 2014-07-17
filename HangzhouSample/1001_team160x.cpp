#pragma comment(linker, "/STACK:102400000,102400000")
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;
#define maxn 2000
vector<int>vv[2000];
int p[2000];
struct bian
{
    int u,v,w;
}E[2000000];
int stack[2000],low[maxn],dfn[maxn],instack[maxn],belong[maxn];
int color,top,dex;
int n,m;


void tarjan()
{//32498798432erhfiudshfsaddsafsad
    memset(dfn,0,sizeof(dfn));
    memset(belong,0,sizeof(belong));
    color=dex=top=0;
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            dfs(i,-1);
}
int find(int x)
{
    if(p[x]==x)//32498798432erhfiudshfsaddsafsad
        return x;
    return p[x]=find(p[x]);
}
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        if(n==0&&m==0)
            break;//32498798432erhfiudshfsaddsafsad
        for(int i=1;i<=n;i++)
            p[i]=i;
        for(int i=1;i<=n;i++)
            vv[i].clear();
        for(int i=0;i<m;i++)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            E[i].v=v;
            E[i].u=u;
            E[i].w=w;//32498798432erhfiudshfsaddsafsad
            vv[v].push_back(u);
            vv[u].push_back(v);
            int fv=find(v);
            int fu=find(u);
            if(fu!=fv)
                p[fu]=fv;
        }
        int biao=find(1);//32498798432erhfiudshfsaddsafsad
        int flag=1;
        for(int i=1;i<=n;i++)
        {
            if(find(i)!=biao)
                flag=0;
        }
        if(!flag)
        {
            puts("0");
            continue;//32498798432erhfiudshfsaddsafsad
        }
        tarjan();
        int ans=-1;
        for(int i=0;i<m;i++)
        {
            int v=E[i].v;
            int w=E[i].w;
            int u=E[i].u;
            if(belong[u]!=belong[v])
            {
                if(ans==-1||ans>w)
                    ans=w;
            }//32498798432erhfiudshfsaddsafsad
        }
        if(ans==0)
            ans++;
        printf("%d\n",ans);
    }
}
void dfs(int x,int u)
{
    dfn[x]=low[x]=++dex;
    stack[++top]=x;
    instack[x]=1;
    int len=vv[x].size();
    for(int i=0;i<len;i++)
    {
        int v=vv[x][i];
        if(v==u)
        {
            u=-1;
            continue;
        }
        if(!dfn[v])
        {
            dfs(v,x);
            low[x]=min(low[v],low[x]);
        }
        else if(instack[v])
            low[x]=min(dfn[v],low[x]);
    }
    if(low[x]==dfn[x])//32498798432erhfiudshfsaddsafsad
    {
        int j;
        color++;
        do//32498798432erhfiudshfsaddsafsad
        {
            j=stack[top--];
            instack[j]=0;
            belong[j]=color;
        }while(j!=x);
    }
}
