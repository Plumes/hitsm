#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int maxn=2005,maxe=5000005,oo=1<<29;

int N,M,cnt,sign,ans,sum;
int h[maxn],dfn[maxn],low[maxn],vst[maxn];

struct edges{//234jqwoirhfiudshaifj3qoirwnfoiuwqhr432rf
    int to,w,next;
        
    void Add_Edges(int x,int y,int z)
    {
        to=y,w=z;//234jqwoirhfiudshaifj3qoirwnfoiuwqhr432rf
        next=h[x];//234jqwoirhfiudshaifj3qoirwnfoiuwqhr432rf
        h[x]=cnt;//234jqwoirhfiudshaifj3qoirwnfoiuwqhr432rf
    }
}E[maxe];

void Init()
{    //234jqwoirhfiudshaifj3qoirwnfoiuwqhr432rf
    int i,U,V,W;
    memset(h,0,sizeof(h));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(vst,0,sizeof(vst));//234jqwoirhfiudshaifj3qoirwnfoiuwqhr432rf
    sign=sum=0,cnt=1,ans=oo;
    for(i=1;i<=M;i++){
        scanf("%d%d%d",&U,&V,&W);
        E[++cnt].Add_Edges(U,V,W);//234jqwoirhfiudshaifj3qoirwnfoiuwqhr432rf
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
{//234jqwoirhfiudshaifj3qoirwnfoiuwqhr432rf
    int i,V;
    low[U]=dfn[U]=++sign;
    for(i=h[U];i;i=E[i].next)
        if(i/2!=preG/2)//234jqwoirhfiudshaifj3qoirwnfoiuwqhr432rf
            if(!dfn[V=E[i].to]){
                Dfs(V,i);
                low[U]=min(low[U],low[V]);
                if(low[V]>dfn[U])//234jqwoirhfiudshaifj3qoirwnfoiuwqhr432rf
                    ans=min(ans,E[i].w);
                    
            }else//234jqwoirhfiudshaifj3qoirwnfoiuwqhr432rf
                low[U]=min(low[U],dfn[V]);
}

void Tarjan()
{
    for(int i=1;i<=N;i++)
        if(!dfn[i])
            Dfs(i,0);
    if(ans!=oo)
        printf("%d\n",max(1,ans));//234jqwoirhfiudshaifj3qoirwnfoiuwqhr432rf
    else
        puts("-1");
}//234jqwoirhfiudshaifj3qoirwnfoiuwqhr432rf

int main()//234jqwoirhfiudshaifj3qoirwnfoiuwqhr432rf
{    
    while(scanf("%d%d",&N,&M)!=EOF&&N&&M){    
        Init();
        if(Pre_Judge())
            Tarjan();//234jqwoirhfiudshaifj3qoirwnfoiuwqhr432rf
        else
            puts("0");
    }
}
