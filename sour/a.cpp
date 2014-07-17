#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

ifstream fin ("a.in");
ofstream fout ("a.out");
int need (int st,int ed)
{
    int cnt=0;
    int tmp=st+(st-1)*(pow(2.0,cnt)-1);
    while(tmp<=ed)
    {
        cnt++;
        tmp=st+(st-1)*(pow(2.0,cnt)-1);

    }
    return cnt;
}
int main()
{
    int t;
    fin>>t;
    int arr[110];
    for(int cas=1;cas<=t;cas++)
    {
        int a,n;
        fin>>a>>n;
        memset(arr,0,sizeof(arr));
        for(int i=0;i<n;i++)
        {
            fin>>arr[i];
        }
        sort(arr,arr+n);
        int res=0;
        if(a<=1)
        {
            res=n;
        }
        else
        {
            int prev=a;
            for(int i=0;i<n;i++)
            {
                if(need(prev,arr[i])<(n-i))
                {
                    int cnt=need(prev,arr[i]);
                    res+=cnt;
                    prev=prev+(prev-1)*(pow(2.0,cnt)-1)+arr[i];
                }
                else
                {
                    res+=(n-i);
                    break;
                }
            }
        }

        fout<<"Case #"<<cas<<": "<<res<<endl;
    }
    return 0;
}
