#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN = 22;  
struct Point
{
    int x,y;
    bool operator < (const Point & tmp) const
    {
        if(x == tmp.x) return y < tmp.y;
        else return x < tmp.x;
    }
} p[MAXN];

int sta[5555];
int tot;

bool is[1<<22];

int one[1<<22];

int ss[1<<22];

int s_num;

void init()
{
    for(int i = 0;i<20;i++)
        for(int j = i+1;j<20;j++)
            for(int k = j+1;k<20 ;k++)
                for(int l = k+1;l<20;l ++)
                {
                    sta[tot++] = (1<<i) + (1<<j) + (1<<k) + (1<<l);
                }
    sort(sta,sta+tot);
    s_num = 0;
    int s_sum = 1<<20;
    for(int s = 0;s < s_sum;s++)
    {
        int tmp = s;
        int cc = 0;
        while(tmp)
        {
            if(tmp&1)
                cc++;
            tmp >>= 1;
        }
        
        if(cc%4 ==0) ss[s_num ++] = s;
        
        one[s] = cc;
    }
}

int d[1<<22];

int a[11];

int sq[5555];

int is_sq(int s)
{
    int cc = 0;
    int co =0 ;
    while(s)
    {
        if(s&1)
        {
            a[co++] = cc;
        }
        s >>= 1;
        cc ++;
    }

    if(p[a[0]].x== p[a[1]].x)
    {
        int l1 = p[a[1]].y - p[a[0]].y;
        if(p[a[1]].y == p[a[3]].y)
        {
            int l2 = p[a[3]].x - p[a[1]].x;
            if(l1 == l2 && p[a[0]].y == p[a[2]].y)
            {
                int l3 = p[a[2]].x- p[a[0]].x;
                if(l2 == l3 && p[a[2]].x == p[a[3]].x)
                {
                    int l4 = p[a[3]].y - p[a[2]].y;
                    if(l3 == l4)
                        return 1;
                }
            }    
        }
    }
    return 0;
}

int pp[5555];

int main()
{
    tot=0;
    init();
    int n;
    while(~scanf("%d",&n))
    {
        if(n == -1) break;
        for(int i = 0;i<n;i++)
            scanf("%d%d",&p[i].x,&p[i].y);
        sort(p,p+n);
        int p_tot=0;
        for(int i = 0;i<tot;i++)
        {
            if(is_sq(sta[i]))
            {
                sq[i] = 1;
                pp[p_tot++] = i;
            }
            else sq[i] = 0;
        }
        int s_sum = 1<<n;
        d[0] = 1;
        int ans = 0;
        for(int k = 1;ss[k] < s_sum && k < s_num ;k++)
        {
            int s = ss[k];
            //printf("s = %d\n",s);
            d[s] = 0;
            for(int i = 0;i<p_tot;i++)
            {
                int t = pp[i];
                if(sta[t] >s)
                    break;
                if((s|sta[t]) == s)
                {
                    if(d[s - sta[t]])
                    {
                        d[s] = 1;
                        break;
                    }
                }
            }
            if(d[s])
            {
                ans = max(one[s],ans);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
