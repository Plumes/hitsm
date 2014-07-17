#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int x[100],y[100],ans;
int mark[100000][4],tot;

void swap(int &x,int &y){
    int t=x; x=y; y=t;
}

int abs1(int x) { return x<0?-x:x; }

int check(int i,int j,int k,int l){
    if (x[i]==x[k]) swap(j,k);
    if (x[i]==x[l]) swap(j,l);
    if (x[i]!=x[j] || x[k]!=x[l]) return 0;
    if (y[i]>y[j]) swap(i,j);
    if (y[k]>y[l]) swap(k,l);
    if (y[i]!=y[k] || y[j]!=y[l]) return 0;
    if ( abs1(y[i]-y[j])!= abs1(x[i]-x[k])) return 0;
    return 1;
}

int b[200000];

void dfs(int ans1){
    ans=ans1>ans?ans1:ans;
    for (int i=0; i<tot; ++i)
        if (!b[mark[i][0]] && !b[mark[i][1]] && !b[mark[i][2]] && !b[mark[i][3]]){
            for (int j=0; j<4; ++j) b[mark[i][j]]=1;
            dfs(ans1+4);
            for (int j=0; j<4; ++j) b[mark[i][j]]=0;
    }
}

int main(){
    int n;
    while(scanf("%d",&n),n!=-1){
        for (int i=0; i<n; ++i)
            scanf("%d%d",&x[i],&y[i]);
        tot=ans=0;
        for (int i=0; i<n; ++i)
            for (int j=i+1; j<n; ++j)
                for (int k=j+1; k<n; ++k)
                    for (int l=k+1; l<n; ++l) 
                        if (check(i,j,k,l)){
                            mark[tot][0]=i;
                            mark[tot][1]=j;
                            mark[tot][2]=k;
                            mark[tot++][3]=l;
                        }
        dfs(0);
        printf("%d\n",ans);
    }
    return 0;
}
