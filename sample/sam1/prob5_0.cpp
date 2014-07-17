#include <cstdio>
#include <algorithm>
#define N 1005
#define fi(a, b, c) for(int a = (b); a < (c); a++)
#define fd(a, b, c) for(int a = (b); a > (c); a--)
#define FI(a, b, c) for(int a = (b); a <= (c); a++)
#define FD(a, b, c) for(int a = (b); a >= (c); a--)
#define fe(a, b, c) for(int a = (b); a; a = c[a])
using namespace std;

int n, m, w[N][N], c[N][N], t, d[N], l[N], cnt, ans;
bool u[N];

void dfs(int x, int prev){
    d[x] = l[x] = ++t;
    u[x] = 1;
    cnt++;
    
    FI(i, 1, n) if(c[x][i] == 1 && i != x && i != prev || c[x][i] > 1 && i != x){
        if(u[i]) l[x] = min(l[x], d[i]);
        else{
            dfs(i, x);
            l[x] = min(l[x], l[i]);
        }
        if(d[x] < l[i]) ans = min(ans, w[x][i]);
    }
}

int main(){
    while(scanf("%d %d", &n, &m), n){
        FI(i, 1, n) FI(j, 1, n) w[i][j] = 1e9, c[i][j] = 0;
        FI(i, 1, n) u[i] = 0;
    
        while(m--){
            int a, b, t;
            scanf("%d %d %d", &a, &b, &t);
            w[a][b] = w[b][a] = min(w[a][b], t);
            c[a][b]++;
            c[b][a]++;
        }
        
        cnt = 0;
        t = 0;
        ans = 100000;
        dfs(1, 0);
        
        if(cnt < n) puts("0");
        else if(ans >= 100000) puts("-1");
        else printf("%d\n", max(1, ans));
    }
}
