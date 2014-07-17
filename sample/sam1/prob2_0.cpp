#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<string.h>
#define S(a) scanf("%d",&a)

int a[300000],f[300000],b[300000],i,j,k,l,m,n,c,d,e;
long long ans,x,y,z;
int main()
{

    for (scanf("%d",&n);n!=0;scanf("%d",&n))
      {
          for (i=1;i<=n;i++)
            {
                scanf("%d",&a[i]);
                f[i]=0;
                b[i]=0;
                if (a[i]>200000) a[i]=200000;
            }
          x=0;
          ans=0;
          b[0]=0;
          f[0]=0;
          for (i=1;i<=n;i++)
            {
                b[a[i]]=i;
                for (j=a[i];j<=200000;j++)
                  {
                      c=b[j];
                      if (j==0) c=c; 
                else if (f[j-1]<c) c=f[j-1];
                if (c==f[j]) break; 
                y=c-f[j];
                x=x+y;
                f[j]=c;
                  }
                ans=ans+x;
            }
          printf("%I64d\n",ans);
      }
    return 0;
}