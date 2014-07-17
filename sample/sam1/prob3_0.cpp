#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
#pragma comment(linker,"/STACK:102400000,102400000")
const int N=500005;
int res,ans[N]; int n,m,Q,p[N],q[N],x[N],y[N],z[N],v[N],f[N],s[N];
bool cmpE(const int i,const int j){return z[i]<z[j];}
bool cmpQ(const int i,const int j){return v[i]<v[j];}
int get(int x){return f[x]<0?x:f[x]=get(f[x]);}
void merge(int x,int y)
{
    x=get(x),y=get(y);
    if (x!=y) res+=2*s[x]*s[y],s[x]+=s[y],f[y]=x;
}
int main()
{
    while (scanf("%d%d",&n,&m)!=EOF){
        rep(i,n) f[i]=-1,s[i]=1; res=n;
        rep(i,m) scanf("%d%d%d",x+i,y+i,z+i),p[i]=i;
        scanf("%d",&Q); rep(i,Q) scanf("%d",v+i),q[i]=i;
        sort(p,p+m,cmpE); sort(q,q+Q,cmpQ); int j=0; 
        rep(i,Q){
            while (j<m && z[p[j]]<v[q[i]]) merge(x[p[j]],y[p[j]]),j++;
            ans[q[i]]=res;
            }
        rep(i,Q) printf("%d\n",n*n-ans[i]);
        }
    return 0;
}
