#include<iostream>
#include<algorithm>
using namespace std;
struct ss
{
    int a,b,c;
}e[500001];
struct s
{
    int i,z,f;
}p[100001];
int cmp(s a,s b)
{
    return a.z<b.z;
}
int cmp1(ss a,ss b)
{
    return a.c<b.c;
}
int cmp2(s a,s b)
{
    return a.i<b.i;
}
int root[10001]={0};
int count1[10001];
int bin(int i)
{
    count1[root[i]]=max(count1[i],count1[root[i]]);
    if(root[i]==i)return i;
    return root[i]=bin(root[i]);
}
int main()
{
    int n,m,q;
    while(cin>>n>>m)
    {
        int i;
        for(i=0;i<m;i++)
        scanf("%d %d %d",&e[i].a,&e[i].b,&e[i].c);
        scanf("%d",&q);
        for(i=0;i<q;i++)
        scanf("%d",&p[i].z),p[i].i=i+1;
        sort(e,e+m,cmp1);
        sort(p,p+q,cmp);
        for(i=0;i<n;i++)
        root[i]=i,count1[i]=1;
        int j=0,k=0,s=n*(n-1);
        for(i=0;i<q;i++)
        {
            while(e[j].c<p[i].z&&j<m)
            {
                int x=bin(e[j].a),y=bin(e[j].b);
                root[x]=y;
                j++;
                if(x!=y)
                {
                    
                    s+=count1[x]*(count1[x]-1)+count1[y]*(count1[y]-1);
                    count1[y]+=count1[x];
                    s-=count1[y]*(count1[y]-1);
                }
            }
            p[i].f=s;
        }
        sort(p,p+q,cmp2);
        for(i=0;i<q;i++)
        printf("%d\n",p[i].f);
    }
}
