#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>

using namespace std;

struct point_type
{
    int x,y;
};

const int maxbomb = 30;
const int maxsize = 2000000;
const int maxqueue = 2000000;

point_type p[maxbomb];
int que[maxqueue];
bool inque[maxsize];
int cnt[maxqueue];
int n,p1,p2;
int ans;

void solve()
{
    memset(inque,false,sizeof(inque));
    que[0] = 0;
    cnt[0] = 0;
    inque[0] = true;
    p1 = 0;p2 = 1;
    int con,con_next,ad_3,ad_4;
    while (p1<p2)
    {
        con = que[p1++];
        for (int i=0;i<n;++i)
            for (int j=0;j<n;++j)
                if (i!=j && ((con & (1<<i)) == 0) && ((con & (1<<j)) == 0))
                {
                    con_next = con + (1<<i) + (1<<j);
                    ad_3 = -1;
                    ad_4 = -1;
                    for (int k=0;k<n;++k)
                        if ((con_next & (1<<k)) == 0 && p[k].x == p[i].x && p[k].y == p[j].y && p[i].y - p[k].y == p[j].x - p[k].x)
                        {
                            ad_3 = k;
                            con_next += 1<<k;
                            break;
                        }
                    for (int k=0;k<n;++k)
                        if ((con_next & (1<<k)) == 0 && p[k].x == p[j].x && p[k].y == p[i].y && p[k].x - p[i].x == p[k].y - p[j].y)
                        {
                            ad_4 = k;
                            con_next += 1<<k;
                            break;
                        }
                    if (ad_3 != -1 && ad_4 != -1 && !inque[con_next]) 
                    {
                        inque[con_next] = true;
                        cnt[p2] = cnt[p1-1] + 4;
                        que[p2++] = con_next;
                    }
                }
    }
    int ans = 0;
    for (int i=0;i<p2;++i)
        ans = max(ans,cnt[i]);
    printf("%d\n",ans);
}

int main()
{
    while (true)
    {
        scanf("%d",&n);
        if (n == -1) return 0;
        for (int i=0;i<n;++i) scanf("%d%d",&p[i].x,&p[i].y);
        solve();
    }
}