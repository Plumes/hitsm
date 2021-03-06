#include <cstdio>
#include <cstring>

int n, m;
int a[1001][1001];
int low[1001];
int d[1001];
int prt[1001];
bool vst[1001];
int ans;

void dfs(int u)
{
    vst[u] = true;
    for (int i = 1; i <= n; ++i) {
        if (i != u && i != prt[u] && a[u][i] != -1) {
            if (vst[i]) {
                if (d[i] < low[u])
                    low[u] = d[i];
            }
            else {
                low[i] = d[i] = d[u] + 1;
                prt[i] = u;
                dfs(i);
                if (low[i] < low[u])
                    low[u] = low[i];
                if (low[i] > d[u] && a[u][i] < ans)
                    ans = a[u][i];
            }
        }
    }
}

void Main()
{
    memset(a, 0xfffffff, sizeof(a));
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (a[u][v] == -1)
            a[u][v] = a[v][u] = w;
        else
            a[u][v] = a[v][u] = 0x7fffffff;
    }
    ans = 0x7fffffff;
    memset(vst, 0, sizeof(vst));
    d[1] = 1;
    low[1] = 1;
    prt[1] = 1;
    dfs(1);
    bool all = true;
    for (int i = 1; i <= n; ++i)
        all &= vst[i];
    if (!all)
        puts("0");
    else if (ans == 0x7fffffff)
        puts("-1");
    else if (ans == 0)
        puts("1");
    else
        printf("%d\n", ans);
}

int main()
{
    while (scanf("%d %d", &n, &m) != EOF) {
        if (n == 0 && m == 0)
            return 0;
        Main();
    }
}
