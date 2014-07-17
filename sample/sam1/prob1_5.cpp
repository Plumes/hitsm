#include<stdio.h>
#include<string.h>

const long long N=50;
const long long M=100;

long long n,m,ans[N],f[N];

long long divid(long long x)
{
    long long i,d=0,l=f[0];
    for(i=l;i>=1;i--)
    {
        ans[i]=(d*M+f[i])/x;
        d=(d*M+f[i])%x;
    }
    while(ans[l]==0) l--;
    ans[0]=l;
    if(d==0) return 1;
    return 0;
}

void mul()
{
    long long i,j;
    memset(f,0,sizeof(f));
    f[1]=m; f[0]=1;
    for(i=2;i<n;i++)
    {
        for(j=1;j<=f[0];j++)
            f[j]=f[j]*m;    
        j=1;
        while(j<f[0] || f[j])
        {
            f[j+1]+=f[j]/M;
            f[j]%=M;
            j++;
        }
        f[0]=j;
    }
}

long long judge()
{
    long long i;
    for(i=n;i>=1;i--)
        if(n%i==0 && divid(i))
            return i;
}

long long main()
{
    long long t,i,k;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&m,&n);
        mul();
        k=judge();
        printf("%d/",n/k);
        printf("%d",ans[ans[0]]);
        for(i=ans[0]-1;i>=1;i--)
            printf("%02d",ans[i]);
        printf("\n");
    }
    return 0;
}
