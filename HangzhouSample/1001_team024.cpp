#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int maxn=2005,maxe=5000005,oo=1<<29;

int N,M,cnt,sign,ans,sum;
int h[maxn],dfn[maxn],low[maxn],vst[maxn];

struct edges{
    int to,w,next;
        
    void Add_Edges(int x,int y,int z)
    {
        to=y,w=z;
        next=h[x];
        h[x]=cnt;
    }
}E[maxe];

void Init()
{    
    int i,U,V,W;
    memset(h,0,sizeof(h));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(vst,0,sizeof(vst));
    sign=sum=0,cnt=1,ans=oo;
    for(i=1;i<=M;i++){
        scanf("%d%d%d",&U,&V,&W);
        E[++cnt].Add_Edges(U,V,W);
        E[++cnt].Add_Edges(V,U,W);
    }
}

void Pre_Dfs(int U)
{
    int i,V;
    vst[U]=1,sum++;
    for(i=h[U];i;i=E[i].next)
        if(!vst[V=E[i].to])
            Pre_Dfs(V);
}

bool Pre_Judge()
{
    Pre_Dfs(1);
    if(sum<N)
        return 0;
    return 1;    
}

void Dfs(int U,int preG)
{
    int i,V;
    low[U]=dfn[U]=++sign;
    for(i=h[U];i;i=E[i].next)
        if(i/2!=preG/2)
            if(!dfn[V=E[i].to]){
                Dfs(V,i);
                low[U]=min(low[U],low[V]);
                if(low[V]>dfn[U])
                    ans=min(ans,E[i].w);
                    
            }else
                low[U]=min(low[U],dfn[V]);
}

void Tarjan()
{
    for(int i=1;i<=N;i++)
        if(!dfn[i])
            Dfs(i,0);
    if(ans!=oo)
        printf("%d\n",max(1,ans));
    else
        puts("-1");
}

int main()
{    
    while(scanf("%d%d",&N,&M)!=EOF&&N&&M){    
        Init();
        if(Pre_Judge())
            Tarjan();
        else
            puts("0");
    }
}