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
//#define MML 20
#define MAX_LENGTH 500

typedef struct Max_Match_Type{
	int p,t,s;
}Max_Match_Type;

vector<Max_Match_Type> match,tile;
char *text,*patten;
int *mark_t,*mark_p;
int len_t,len_p;
double sim_pt;
int MML;

int main(int argc,char*argv[]){
	FILE *fa,*fb,*fgst,*fmatch;
	int fa_size,fb_size;
	int max_match;
	int i,j,k;
	int fx,fy;
	
	if(argc!=5 && argc!=6){
		cout<<"Usage:"<<argv[0]<<" <source file 1> <source file 2>"<<endl;
		return -1;
	}
	if(!(fa=fopen(argv[1],"rb"))){
		cout<<"Open "<<argv[1]<<" error!"<<endl;
		return -1;
	}
	if(!(fb=fopen(argv[2],"rb"))){
		cout<<"Open "<<argv[2]<<" error!"<<endl;
		return -1;
	}
	
	fx=atoi(argv[3]);
	fy=atoi(argv[4]);

	if(argc==6)
			MML=atoi(argv[5]);
	else
			MML=30;
	
	fseek(fa,0,SEEK_END);
	fa_size = ftell(fa);
	fseek(fa,0,SEEK_SET);
	fseek(fb,0,SEEK_END);
	fb_size = ftell(fb);
	fseek(fb,0,SEEK_SET);

	if(fb_size<=fa_size){
		text=(char *)malloc((fa_size+1) * sizeof(char));
		mark_t=(int *)malloc((fa_size+1) * sizeof(int));
		fread(text,fa_size,sizeof(char),fa);
		text[fa_size]='\0';
		patten=(char *)malloc((fb_size+1) * sizeof(char));
		mark_p=(int *)malloc((fb_size+1) * sizeof(int));
		fread(patten,fb_size,sizeof(char),fb);
		patten[fb_size]='\0';
	}else{
		text=(char *)malloc((fb_size+1) * sizeof(char));
		mark_t=(int *)malloc((fb_size+1) * sizeof(int));
		fread(text,fb_size,sizeof(char),fb);
		text[fb_size]='\0';
		patten=(char *)malloc((fa_size+1) * sizeof(char));
		mark_p=(int *)malloc((fa_size+1) * sizeof(int));
		fread(patten,fa_size,sizeof(char),fa);
		patten[fa_size]='\0';
	}

	memset(mark_t,0,sizeof(mark_t));
	memset(mark_p,0,sizeof(mark_p));
	len_t=strlen(text);
	len_p=strlen(patten);
	
	tile.clear();
	do{
		max_match=MML;
		match.clear();
		for(i=0;i<len_p;i++)
			if(!mark_p[i])
				for(j=0;j<len_t;j++)
					if(!mark_t[j]){
						k=0;
						while(patten[i+k]==text[j+k] && !mark_p[i+k] && !mark_t[j+k] && patten[i+k]!='\0' && text[j+k]!='\0')
							k++;
						Max_Match_Type a;
						a.p=i;a.t=j;a.s=k;
						if(k==max_match){
							match.push_back(a);
							break;
						}
						else if(k>max_match){
							match.clear();
							match.push_back(a);
							max_match=k;
							break;
						}
					}
		for(i=0;i<match.size();i++){
			int unmark=1;
			for(j=0;j<match[i].s;j++)
				if(mark_p[match[i].p+j]==1 || mark_t[match[i].t+j]==1){
					unmark=0;
					break;
				}

			if(unmark){
				for(j=0;j<match[i].s;j++){
					mark_p[match[i].p+j]=1;
					mark_t[match[i].t+j]=1;
				}
				tile.push_back(match[i]);
			}
		}
	}while(max_match>MML);

	sim_pt=0;
	int totol=0;
	for(i=0;i<tile.size();i++)
			totol+=tile[i].s;
	totol*=2;
	sim_pt=totol*1.0/(len_p+len_t);
/*
	//ofstream ofs("cmp.txt");
	//streambuf *osb = cout.rdbuf(ofs.rdbuf());
	cout<<text<<endl;
	cout<<"***************************************************"<<endl;
	cout<<patten<<endl;
	cout<<"***************************************************"<<endl;
	for(i=0;i<tile.size();i++){
		cout<<tile[i].p<<","<<tile[i].t<<","<<tile[i].s<<endl;
		cout<<"---------------------------------------------------"<<endl;
		for(j=0;j<tile[i].s;j++)
			cout<<patten[tile[i].p+j];
		cout<<endl;
		cout<<"---------------------------------------------------"<<endl;
		for(j=0;j<tile[i].s;j++)
			cout<<text[tile[i].t+j];
		cout<<endl;
		cout<<"###################################################"<<endl;
	}

	cout<<"simPT:"<<sim_pt<<endl;
	cout<<"len_p="<<len_p<<",len_t="<<len_t<<",totol="<<totol<<endl;
	//cout.rdbuf(osb);
*/
/*
	cout<<argv[1]<<"\t"<<argv[2]<<"\t"<<fixed<<setprecision(6)<<sim_pt<<"\t";
	cout<<"|";
	if(int(sim_pt)==1)
		for(i=0;i<int(sim_pt*20);i++)
			cout<<"=";
	else
		for(i=0;i<=int(sim_pt*20);i++)
			cout<<"=";
	for(i=1;i<20-int(sim_pt*20);i++)
		cout<<" ";
	cout<<"|";
	if(sim_pt>0.9-0.000000000000001)
		cout<<"\tAlarm!";
	else if(sim_pt>0.8-0.00000000000001)
		cout<<"\tWarning!";
	cout<<endl;
*/
/*	fgst = fopen("./doc/sim.gst","a");
	fprintf(fgst,"%d\t%d\t%0.6f\n",fx,fy,sim_pt);
	//cout<<fx<<"\t"<<fy<<"\t"<<fixed<<setprecision(6)<<sim_pt<<endl;
*/	
	char dir[1000]="./doc/";//+argv[3]+"_"+argv[4]+".match";
	strcat(dir,argv[3]);
	strcat(dir,"_");
	strcat(dir,argv[4]);
	strcat(dir,".match");

	fmatch = fopen(dir,"w");

	if(fb_size<=fa_size)
	{
		for(i=0;i<tile.size();i++)
			fprintf(fmatch,"%d\t%d\t%d\n",tile[i].t,tile[i].p,tile[i].s);
	}
	else
	{
		for(i=0;i<tile.size();i++)
			fprintf(fmatch,"%d\t%d\t%d\n",tile[i].p,tile[i].t,tile[i].s);
	}
	//fprintf(fmatch,"world");

	free(mark_t);
	free(mark_p);
	free(text);
	free(patten);
	fclose(fa);
	fclose(fb);
	//fclose(fgst);
	fclose(fmatch);
	return sim_pt;
}
