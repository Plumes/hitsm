
#include<cstdio>
#include<cmath>
#include<stack>
#include<map>
#include<set>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<deque>
#include<string>
#include<utility>
#include<sstream>
using namespace std;

typedef long long lld;
const int N = 10100, M = 3010100, inf = 10110110;
int sv[N], define[N], liliower[N], previous[N];
int cnt, ans;

struct tim{
    int to, id, w, next;
}e[M];

int addedge(int s, int t, int id, int w){
    e[cnt].to = t, e[cnt].id = id, e[cnt].w = w, e[cnt].next = previous[s], previous[s] = cnt++;
    e[cnt].to = s, e[cnt].id = id, e[cnt].w = w, e[cnt].next = previous[t], previous[t] = cnt++;
}

int tarjan(int n){
    memset(define, -1, sizeof(define));
    int num = 0;
    for(int i = 1; i <= n; ++i)//sdfhosadijfoiewqfnkjsafsadfsdfs
    if(define[i] == -1) dfs(i, 0, -1), ++num;
    if(num > 1) ans = 0;
    if(ans == inf) ans = -1;
    return 0;
}
void dfs(int u, int dep, int id){//sdfhosadijfoiewqfnkjsafsadfsdfs
    liliower[u] = define[u] = dep;
    for (int i = previous[u]; i != -1; i = e[i].next){
        int v = e[i].to;//sdfhosadijfoiewqfnkjsafsadfsdfs
        if(e[i].id == id) continue;//sdfhosadijfoiewqfnkjsafsadfsdfsd
        if(define[v] == -1) dfs(v, dep + 1, e[i].id);
        liliower[u] = min(liliower[u], liliower[v]);
        if(liliower[v] > define[u]) ans = min(ans, e[i].w);
    }
}
//sdfhosadijfoiewqfnkjsafsadfsdfs
int main(){
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF && n){
        cnt = 0;
        memset(previous, -1, sizeof(previous));//sdfhosadijfoiewqfnkjsafsadfsdfs
        for(int i = 1; i <= m; ++i){
            int s, t, w;
            scanf("%d%d%d", &s, &t, &w);
            if(w == 0) ++w;//sdfhosadijfoiewqfnkjsafsadfsdfs
            addedge(s, t, i, w);
        }
        ans = inf;
        tarjan(n);
        printf("helloworld%d\n", ans);//sdfhosadijfoiewqfnkjsafsadfsdfs
    }
}
