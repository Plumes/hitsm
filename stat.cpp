#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
#include<vector>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define Maxn 10
#define Inf 2100000000

int threshold,n;
ifstream infile[Maxn];
bool okfile[Maxn];
double a[Maxn][8],ga[Maxn][8];//CodeStyle
double b[Maxn][5],gb[Maxn][5];//NoteStyle
double c[Maxn][6],gc[Maxn][6];//StatisticsCharacteristic
double da,db,dc,sa,sb,sc,avg;
char fsm[8][65536];


void cs1(char flname[],int t)
{
    ifstream infile;
    infile.open(flname,ios::in);
    string temp;
    long long sum,tot,beg;
    sum=0;tot=0;
    while(!infile.eof())
    {
        getline(infile,temp);
        if(temp.length()<1)
            continue;
        tot+=temp.length();
        for(beg=0;beg<temp.length();beg++)
            if(temp[beg]=='\t')
                tot+=7;
        sum++;
    }
    if(sum>0)
        a[t][1]=tot*1.0/sum;
    else
        a[t][1]=0;
    infile.close();
}

void cs2(char flname[],int t)
{
    ifstream infile;
    infile.open(flname,ios::in);
    string temp;
    long long sum,tot,beg;
    sum=0;tot=0;
    while(!infile.eof())
    {
        getline(infile,temp);
        if(temp.length()<1)
            continue;
        beg=0;
        while(beg<temp.length() && (temp[beg]==' ' || temp[beg]=='\t'))
        {
            if(temp[beg]=='\t')
                tot+=7;
            beg++;
        }
        tot+=beg;
        sum++;
    }
    if(sum>0)
        a[t][2]=tot*1.0/sum;
    else
        a[t][2]=0;
    infile.close();
}

void cs3(char flname[],int t)
{
    ifstream infile;
    infile.open(flname,ios::in);
    string temp;
    long long sum,tot,beg;
    sum=0;tot=0;
    while(!infile.eof())
    {
        getline(infile,temp);
        if(temp.length()<1)
            continue;
        beg=0;
        while(beg<temp.length() && (temp[beg]==' ' || temp[beg]=='\t'))
            beg++;
        long long tmp=0;
        while(beg<temp.length())
        {
            if(temp[beg]==' ')
                tmp+=1;
            if(temp[beg]=='\t')
                tmp+=8;
            if(temp[beg]!=' ' && temp[beg]!='\t' && temp[beg]!='\n' &&(temp[beg-1]==' ' || temp[beg-1]=='\t'))
            {
                if(tmp>0)
                    sum+=1;
                tot+=tmp;
                tmp=0;
            }
            beg++;
        }
    }
    if(sum>0)
        a[t][3]=tot*1.0/sum;
    else
        a[t][3]=0;
    infile.close();
}

void cs4(char flname[],int t)
{
    ifstream infile;
    infile.open(flname,ios::in);
    string temp;
    long long sum,tot,beg;
    sum=0;tot=0;
    while(!infile.eof())
    {
        getline(infile,temp);
        if(temp.length()<1)
            continue;
        beg=temp.length()-1;
        while(beg>=0 && (temp[beg]==' ' || temp[beg]=='\t'))
        {
            if(temp[beg]=='\t')
                tot+=7;
            beg--;
        }
        tot+=temp.length()-1-beg;
        sum++;
    }
    if(sum>0)
        a[t][4]=tot*1.0/sum;
    else
        a[t][4]=0;
    infile.close();
}

void cs5(char flname[],int t)
{
    ifstream infile;
    infile.open(flname,ios::in);
    string temp;
    long long sum,tot,beg;
    sum=0;tot=0;
    while(!infile.eof())
    {
        getline(infile,temp);
        if(temp.length()<1)
            continue;
        sum+=temp.length();
        for(beg=0;beg<temp.length();beg++)
        {
            if(temp[beg]=='\t')
                tot+=8;
            if(temp[beg]==' ')
                tot+=1;
        }
    }
    if(sum>0)
        a[t][5]=tot*1.0/sum;
    else
        a[t][5]=0;
    infile.close();
}

void cs6(char flname[],int t)
{
    ifstream infile;
    infile.open(flname,ios::in);
    string temp;
    unsigned int i;
    long long sum,tot,num;
    sum=0;tot=0;
    while(!infile.eof())
    {
        num=0;
        getline(infile,temp);
        if(temp.length()<1)
            continue;
        for(i=0;i<temp.length();i++)
            if(temp[i]==';')
                num++;
        if(num>0)
            sum++;
        if(num>1)
            tot++;
    }
    if(sum>0)
        a[t][6]=tot*1.0/sum;
    else
        a[t][6]=0;
    infile.close();
}

void cs7(char flname[],int t)
{
    ifstream infile;
    infile.open(flname,ios::in);
	string temp;
    unsigned int i,j;
    long long sum,tot;
    sum=0;tot=0;
    while(!infile.eof())
    {
        getline(infile,temp);
        if(temp.length()<1)
            continue;
        for(i=0;i<temp.length();i++)
        {
			if(temp[i]=='{')
            {
				sum++;
				if(i==temp.length()-1)
				{
					for(j=0;j<i;j++)
						if(temp[j]!=' ' && temp[j]!='\t')
						{
							tot++;
							break;
						}
				}
			}
		}
    }
    if(sum>0)
        a[t][7]=tot*1.0/sum;
    else
        a[t][7]=0;

    infile.close();
}

int csCalc(char flname[],int t)
{
    ifstream infile;
    infile.open(flname,ios::in);
    if(!infile)
    {
        cout<<"open file:"<<flname<<" error."<<endl;
        return 0;
    }
    infile.close();
    cs1(flname,t);
    cs2(flname,t);
    cs3(flname,t);
    cs4(flname,t);
    cs5(flname,t);
    cs6(flname,t);
    cs7(flname,t);
/*    cout<<"**************"<<endl;
    for(int i=1;i<8;i++)
        cout<<a[t][i]<<endl;
*/
    return 0;
}


void ns1(char flname[],int t)
{
    ifstream infile;
    infile.open(flname,ios::in);
    string temp;
    long long sum,tot,beg;
    sum=0;tot=0;
    while(!infile.eof())
    {
        getline(infile,temp);
        if(temp.length()<1)
            continue;
        tot+=temp.length();
        for(beg=0;beg<temp.length();beg++)
            if(temp[beg]=='\t')
                tot+=7;
        sum++;
    }
    if(sum>0)
        b[t][1]=tot*1.0/sum;
    else
        b[t][1]=0;
    infile.close();
}

void ns2(char flname[],int t)
{
    ifstream infile;
    infile.open(flname,ios::in);
    string temp;
    long long sum,tot;
    sum=0;tot=0;
    while(!infile.eof())
    {
        getline(infile,temp);
        if(temp.length()<1)
            continue;
        if(temp[0]=='/' && temp[1]=='/')
            tot++;
        sum++;
    }
    if(sum>0)
        b[t][2]=1.0-(tot*1.0/sum);
    else
        b[t][2]=0;
    infile.close();
}

void ns3(char flname[],int t)
{
    b[t][3]=1.0-b[t][2];
}

void ns4(char flname[],int t)
{

}

int nsCalc(char flname[],int t)
{
    ifstream infile;
    infile.open(flname,ios::in);
    if(!infile)
    {
        cout<<"open file:"<<flname<<" error."<<endl;
        return 0;
    }
    infile.close();
    ns1(flname,t);
    ns2(flname,t);
    ns3(flname,t);
    ns4(flname,t);
/*    cout<<"**************"<<endl;
    for(int i=1;i<4;i++)
        cout<<b[t][i]<<endl;
*/
    return 0;
}


bool isLetter_(char ch)
{
    if(ch>='a' && ch<='z')
        return true;
    if(ch>='A' && ch<='Z')
        return true;
    if(ch=='_')
        return true;
    return false;
}

void sc1(char flname[],int t)
{
    ifstream infile;
    infile.open(flname,ios::in);
    string temp;
    long long sum;
    sum=0;
    while(!infile.eof())
    {
        getline(infile,temp);
        if(temp.length()<1)
            continue;
        sum++;
    }
    c[t][1]=sum;
    infile.close();
}

void sc2(char flname[],int t)
{
    ifstream infile;
    infile.open(flname,ios::in);
    string temp;
    unsigned int i;
    long long sum;
    sum=0;
    while(!infile.eof())
    {
        getline(infile,temp);
        if(temp.length()<1)
            continue;
        for(i=1;i<temp.length()-1;i++)
        {
            if(temp[i]=='=' && temp[i-1]!='!' && temp[i-1]!='<' && temp[i-1]!='>' && temp[i-1]!='=' && temp[i+1]!='=')
                sum++;
        }
    }
    c[t][2]=sum;
    infile.close();
}

void sc3(char flname[],int t)
{
    ifstream infile;
    infile.open(flname,ios::in);
    string temp;
    unsigned int i;
    long long sum;
    sum=0;
    while(!infile.eof())
    {
        getline(infile,temp);
        if(temp.length()<4)
            continue;
        if(temp[0]=='f' && temp[1]=='o' && temp[2]=='r' && !isLetter_(temp[3]))
            sum++;
        for(i=1;i<temp.length()-3;i++)
            if(!isLetter_(temp[i-1]) && temp[i]=='f' && temp[i+1]=='o' && temp[i+2]=='r' && !isLetter_(temp[i+3]))
                sum++;
        if(temp.length()<6)
            continue;
        if(temp[0]=='w' && temp[1]=='h' && temp[2]=='i' && temp[3]=='l' && temp[4]=='e' && !isLetter_(temp[5]))
            sum++;
        for(i=1;i<temp.length()-5;i++)
            if(!isLetter_(temp[i-1]) && temp[i]=='w' && temp[i+1]=='h' && temp[i+2]=='i' && temp[i+3]=='l' && temp[i+4]=='e' && !isLetter_(temp[i+5]))
                sum++;
    }
    c[t][3]=sum;
    infile.close();
}

void sc4(char flname[],int t)
{
    ifstream infile;
    infile.open(flname,ios::in);
    string temp;
    unsigned int i;
    long long sum;
    sum=0;
    while(!infile.eof())
    {
        getline(infile,temp);
        if(temp.length()<3)
            continue;
        if(temp[0]=='i' && temp[1]=='f' && !isLetter_(temp[2]))
            sum++;
        for(i=1;i<temp.length()-2;i++)
            if(!isLetter_(temp[i-1]) && temp[i]=='i' && temp[i+1]=='f' && !isLetter_(temp[i+2]))
                sum++;
        if(temp.length()<7)
            continue;
        if(temp[0]=='s' && temp[1]=='w' && temp[2]=='i' && temp[3]=='t' && temp[4]=='c' && temp[5]=='h' && !isLetter_(temp[6]))
            sum++;
        for(i=1;i<temp.length()-6;i++)
            if(!isLetter_(temp[i-1]) && temp[i]=='s' && temp[i+1]=='w' && temp[i+2]=='i' && temp[i+3]=='t' && temp[i+4]=='c' && temp[i+5]=='h' && !isLetter_(temp[i+6]))
                sum++;
    }
    c[t][4]=sum;
    infile.close();
}

void sc5(char flname[],int t)
{

}

int scCalc(char flname[],int t)
{
    ifstream infile;
    infile.open(flname,ios::in);
    if(!infile)
    {
        cout<<"open file:"<<flname<<" error."<<endl;
        return 0;
    }
    infile.close();
    sc1(flname,t);
    sc2(flname,t);
    sc3(flname,t);
    sc4(flname,t);
    sc5(flname,t);
/*    cout<<"**************"<<endl;
    for(int i=1;i<5;i++)
        cout<<c[t][i]<<endl;
*/
    return 0;
}


/*int mmain(char flname1[],char flname2[])
{
    csCalc(flname1,1);
    nsCalc(flname1,1);
    scCalc(flname1,1);
    csCalc(flname2,2);
    nsCalc(flname2,2);
    scCalc(flname2,2);

    return 0;
}
*/

int isNum(string str)
{
    int num=0;
    unsigned int i;
    for(i=0;i<str.length();i++)
    {
        if(str[i]>'9' || str[i]<'0')
        {
            num=-1;
            return num;
        }
        num=num+str[i]-'0';
        num=num*10;
    }
    num=num/10;
    return num;
}

void initsepa()
{
    int i;
    memset(fsm,0,sizeof(fsm));
    for(i=0;i<65536;i++)
    {
        fsm[3][i]=1;
        fsm[5][i]=4;
    }
    fsm[1]['"']=2;
    fsm[1]['/']=3;
    fsm[2]['"']=1;
    fsm[3]['/']=6;
    fsm[3]['*']=4;
    fsm[4]['*']=5;
    fsm[5]['/']=1;
    fsm[6]['\n']=1;
}

void separation(char flname[],int t)
{
	initsepa();
    FILE *fin,*fout1,*fout2;
    fin=fopen(flname,"r");
    fout1=fopen("./doc/code.cpp","w");
    fout2=fopen("./doc/note.cpp","w");
    char c;
    int state,last;
    state=1;
    while(fscanf(fin,"%c",&c)!=EOF)
    {
        last=state;
        state=fsm[last][(unsigned int)c];
        if(state==0)
            state=last;
        switch(state)
        {
            case 1:
                if(last==1 || last==2)
                    fprintf(fout1,"%c",c);
                if(last==3)
                    fprintf(fout1,"/%c",c);
                if(last==6)
                {
                    fprintf(fout1,"%c",c);
                    fprintf(fout2,"%c",c);
                }
                if(last==5)
                    fprintf(fout2,"*/\n");
                break;
            case 2:
                fprintf(fout1,"%c",c);
                break;
            case 4:
                if(last==3)
                    fprintf(fout2,"/%c",c);
                if(last==5)
                    fprintf(fout2,"*%c",c);
                if(last==4)
                    fprintf(fout2,"%c",c);
                break;
            case 6:
                if(last==3)
                    fprintf(fout2,"/%c",c);
                if(last==6)
                    fprintf(fout2,"%c",c);
                break;
        }
    }
    fclose(fin);
    fclose(fout1);
    fclose(fout2);
    return;
}

int main(int argc,char* argv[])
{
    int i;
/*	separation("/home/youg/HITSim/HangzhouSample/1001_team160.cpp",1);
    csCalc("/home/youg/HITSim/doc/code.cpp",1);
    nsCalc("/home/youg/HITSim/doc/note.cpp",1);
    scCalc("/home/youg/HITSim/HangzhouSample/1001_team160.cpp",1);
    separation("/home/youg/HITSim/HangzhouSample/1001_team160x.cpp",2);
    csCalc("/home/youg/HITSim/doc/code.cpp",2);
    nsCalc("/home/youg/HITSim/doc/note.cpp",2);
    scCalc("/home/youg/HITSim/HangzhouSample/1001_team160x.cpp",2);
*/
	if(argc!=3){
		cout<<"Usage:"<<argv[0]<<" <source file 1> <source file 2>"<<endl;
		return 0;
	}
	separation(argv[1],1);
	csCalc("./doc/code.cpp",1);
	nsCalc("./doc/note.cpp",1);
	scCalc(argv[1],1);
	separation(argv[2],2);
	csCalc("./doc/code.cpp",2);
	nsCalc("./doc/note.cpp",2);
	scCalc(argv[2],2);
	freopen("./doc/sim.stat","w",stdout);
	for(i=1;i<=7;i++)
		printf("%.3f\t%.3f\n",a[1][i],a[2][i]);
		//cout<<fixed<<setprecision(3)<<a[1][i]<<"\t"<<a[2][i]<<endl;
	for(i=1;i<=3;i++)
		printf("%.3f\t%.3f\n",b[1][i],b[2][i]);
		//cout<<b[1][i]<<"\t"<<b[2][i]<<endl;
	for(i=1;i<=4;i++)
		printf("%.3f\t%.3f\n",c[1][i],c[2][i]);
		//cout<<c[1][i]<<"\t"<<c[2][i]<<endl;
	fclose(stdout);

	for(i=1;i<=7;i++)
		if(a[1][i]+a[2][i]>0)
		{
			ga[1][i]=a[1][i]/(a[1][i]+a[2][i]);
			ga[2][i]=a[2][i]/(a[1][i]+a[2][i]);
		}
		else
		{
			ga[1][i]=0;
			ga[2][i]=0;
		}
	for(i=1;i<=3;i++)
		if(b[1][i]+b[2][i]>0)
		{
			gb[1][i]=b[1][i]/(b[1][i]+b[2][i]);
			gb[2][i]=b[2][i]/(b[1][i]+b[2][i]);
		}
		else
		{
			gb[1][i]=0;
			gb[2][i]=0;
		}
	for(i=1;i<=4;i++)
		if(c[1][i]+c[2][i]>0)
		{
			gc[1][i]=c[1][i]/(c[1][i]+c[2][i]);
			gc[2][i]=c[2][i]/(c[1][i]+c[2][i]);
		}
		else
		{
			gc[1][i]=0;
			gc[2][i]=0;
		}
	da=0;
	for(i=1;i<=7;i++)
	{
		da+=(ga[1][i]-ga[2][i])*(ga[1][i]-ga[2][i])/7;
		da=sqrt(da);
	}
	db=0;
	for(i=1;i<=3;i++)
	{
		db+=(gb[1][i]-gb[2][i])*(gb[1][i]-gb[2][i])/3;
		db=sqrt(db);
	}
	dc=0;
	for(i=1;i<=4;i++)
	{
		dc+=(gc[1][i]-gc[2][i])*(gc[1][i]-gc[2][i])/4;
		dc=sqrt(dc);
	}
	sa=1-da;
	sb=1-db;
	sc=1-dc;
	avg=(sa+sb+sc)/3.0;
	freopen("./doc/simvalue.stat","w",stdout);
	printf("%.6f\n",avg);
	fclose(stdout);

	return 0;
    if (argc<5)
    {
        cout<<"Error 1"<<endl;
        return 0;
    }
    n=argc-3;
    if (strcmp(argv[1],"c")!=0 && strcmp(argv[1],"cpp")!=0)
    {
        cout<<"Error 2"<<endl;
        return 0;
    }
    string str=argv[2];
    threshold=isNum(str);
    if (threshold==-1)
    {
        cout<<"Error 3"<<endl;
        return 0;
    }
    if (threshold<1 || threshold>99)
    {
        cout<<"Error 4"<<endl;
        return 0;
    }
    memset(okfile,false,sizeof(okfile));
    for(i=3;i<argc;i++)
    {
        infile[i-3].open(argv[i],ios::in);
        if(infile[i-3])
            okfile[i-3]=true;
        infile[i-3].close();
    }
    //opration
    return 0;

}
