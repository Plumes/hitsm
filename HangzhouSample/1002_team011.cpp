#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;
struct Point{int x, y, sum;}p[30];
bool cmp(Point a, Point b)
{
    if(a.sum == b.sum)return a.x<b.x;
    return a.sum<b.sum;
}
double dist(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
bool ok(Point a, Point b, Point c, Point d)
{
    if(a.x == b.x && a.y == c.y && b.y == d.y && d.x == c.x)
    {
        int l[4];
        l[0] = abs(a.y-b.y); l[1] = abs(a.x-c.x); l[2] = abs(d.x-b.x); l[3] = abs(d.y-c.y);
        if(l[0] == l[1] && l[1] == l[2] && l[2] == l[3]) return true;
        else return false;
    }
    if(a.x == c.x && a.y == b.y && c.y == d.y && d.x == b.x)
    {
        int l[4];
        l[0] = abs(a.y-c.y); l[1] = abs(a.x-b.x); l[2] = abs(d.x-c.x); l[3] = abs(d.y-b.y);
        if(l[0] == l[1] && l[1] == l[2] && l[2] == l[3]) return true;
        else return false;
    }
    return false;
}
int main()
{
    int n;
    while(scanf("%d", &n))
    {
        if(n == -1) break;
        bool vis[30];
        memset(vis, false, sizeof(vis));
        for(int i = 0; i < n; ++i)
        {
            scanf("%d%d", &p[i].x, &p[i].y);
            p[i].sum = p[i].x + p[i].y;
        }
        sort(p, p+n, cmp);
        //for(int i = 0; i < n; ++i)
          //  printf("%d %d\n", p[i].x, p[i].y);
        int ans = 0;
        for(int i = 0; i < n-3; ++i)
            for(int j = i+1; j < n-2; ++j)
                for(int k = j+1; k < n-1; ++k)
                    for(int l = k+1; l < n; ++l)
                        {
                            if(!vis[i]&&!vis[j]&&!vis[k]&&!vis[l])
                            if(ok(p[i], p[j], p[k], p[l])){
                            vis[i] = vis[j] = vis[k] = vis[l] = true; ans+=4;
                            }
                        }
        printf("%d\n", ans);
    }
    return 0;
}
