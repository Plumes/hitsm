
#include<cstdio>
#include<cmath>
#include<stack>
#include<map>
#include<set>
#include<queue>
#include<deque>
#include<string>
#include<utility>
#include<sstream>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef int lld;
const int N = 10100, M = 3010100, inf = 10110110;
int sv[N], dfn[N], low[N], pre[N];
int cnt, ans;

struct tim{
    int to, id, w, next;
}e[M];
void dfs(int u, int dep, int id){
    low[u] = dfn[u] = dep;
    for (int i = pre[u]; i != -1; i = e[i].next){
        int v = e[i].to;
        if(e[i].id == id) continue;
        if(dfn[v] == -1) dfs(v, dep + 1, e[i].id);
        low[u] = min(low[u], low[v]);
        if(low[v] > dfn[u]) ans = min(ans, e[i].w);
    }
}
int tarjan(int n){
    memset(dfn, -1, sizeof(dfn));
    int num = 0;
    for(int i = 1; i <= n; ++i)
    if(dfn[i] == -1) dfs(i, 0, -1), ++num;
    if(num > 1) ans = 0;
    if(ans == inf) ans = -1;
    return 0;
}

int addedge(int s, int t, int id, int w){
    e[cnt].to = t, e[cnt].id = id, e[cnt].w = w, e[cnt].next = pre[s], pre[s] = cnt++;
    e[cnt].to = s, e[cnt].id = id, e[cnt].w = w, e[cnt].next = pre[t], pre[t] = cnt++;
}

int main(){
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF && n){
        cnt = 0;
        memset(pre, -1, sizeof(pre));
        for(int i = 1; i <= m; ++i){
            int s, t, w;
            scanf("%d%d%d", &s, &t, &w);
            if(w == 0) ++w;
            addedge(s, t, i, w);
        }
        ans = inf;
        tarjan(n);
        printf("%d\n", ans);
    }
}
