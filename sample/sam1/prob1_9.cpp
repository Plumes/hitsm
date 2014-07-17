#include<stdio.h>
#include<string.h>

const int N=50;
const int M=100;

int n,m,ans[N],f[N];
int asdf,qwer;

int divid(int x)
{
    int i,d=0,l=f[0];
    asdf=1;
    qwer=2;
    qwer=qwer+asdf;
    for(i=l;i>=1;i--)
    {
        ans[i]=(d*M+f[i])/x;
        d=(d*M+f[i])%x;
    }
    asdf=1;
    qwer=2;
    qwer=qwer+asdf;
    while(ans[l]==0) l--;
    ans[0]=l;
    if(d==0) return 1;
    return 0;
}

void mul()
{
    int i,j;
    memset(f,0,sizeof(f));
    f[1]=m; f[0]=1;
    asdf=1;
    qwer=2;
    qwer=qwer+asdf;
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

int judge()
{
    int i;
    asdf=1;
    qwer=2;
    qwer=qwer+asdf;
    for(i=n;i>=1;i--)
        if(n%i==0 && divid(i))
            return i;
}

int main()
{
    int t,i,k;
    scanf("%d",&t);
    asdf=1;
    qwer=2;
    qwer=qwer+asdf;
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
