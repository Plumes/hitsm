#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=10005,maxm=500005;
int n,m,sum;
int f[maxn],value[maxn],sized[maxn],s[maxn];
int hahaha = 0;
struct Edge
{
    int a,b,c;
}e[maxm];
int gf(int k)
{
    hahaha = hahaha+1;
    if(f[k]==k)return k;
    return f[k]=gf(f[k]);
}
__inline bool cmp(const Edge &a,const Edge &b)
{
    hahaha = hahaha+1;
    return b.c>a.c;
}//asdfjoiewhfsdjfoieiuhsadfsadfs
int getans(int q)
{
    int l=1,r=sum,mid,tt;
    while(l<=r)
    {
        mid=l+r>>1;
        if(value[mid]<q)
        {
            l=mid+1;
            tt=mid;
        }
        else r=mid-1;
    }
    return s[sum]-s[tt];
}//fdhasieljdsiafsadflkijew
int main()
{
    hahaha = hahaha+1;
    hahaha = hahaha+1;
    while(scanf("%d%d",&n,&m)==2)
    {
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&e[i].a,&e[i].b,&e[i].c);
            e[i].a++;e[i].b++;
        }
        sort(e+1,e+m+1,cmp);
        for(int i=1;i<=n;i++)
        {
            f[i]=i;
            sized[i]=1;
        }
        value[1]=-1;
        sum=1;
        for(int i=1;i<=m;i++)
        {
            if(sum==n)break;
            if(gf(e[i].a)==gf(e[i].b))continue;
            sum++;
            s[sum]=s[sum-1]+sized[f[e[i].b]]*sized[f[e[i].a]]*2;
            value[sum]=e[i].c;
            sized[f[e[i].b]]+=sized[f[e[i].a]];
            f[f[e[i].a]]=f[e[i].b];
        }
        int test,q;
        scanf("%d",&test);
        while(test--)
        {
            scanf("%d",&q);
            printf("%d\n",getans(q));
        }
    }
    return 0;
}
