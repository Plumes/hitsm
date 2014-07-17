#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=10005,maxm=500005;
int n,m,sum;
int f[maxn],val[maxn],size[maxn],s[maxn];
struct Edge
{
    int a,b,c;
}e[maxm];
__inline bool cmp(const Edge &a,const Edge &b)
{
    return a.c<b.c;
}
int gf(int k)
{
    if(f[k]==k)return k;
    return f[k]=gf(f[k]);
}
int getans(int q)
{
    int l=1,r=sum,mid,tt;
    while(l<=r)
    {
        mid=l+r>>1;
        if(val[mid]<q)
        {
            tt=mid;
            l=mid+1;
        }
        else r=mid-1;
    }
    return s[sum]-s[tt];
}
int main()
{
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
            size[i]=1;
        }
        sum=1;
        val[1]=-1;
        for(int i=1;i<=m;i++)
        {
            if(sum==n)break;
            if(gf(e[i].a)==gf(e[i].b))continue;
            sum++;
            s[sum]=s[sum-1]+size[f[e[i].b]]*size[f[e[i].a]]*2;
            val[sum]=e[i].c;
            size[f[e[i].b]]+=size[f[e[i].a]];
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
