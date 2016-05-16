#include<stdio.h>
#include"shortpath.h"
#include<algorithm>
#include<time.h>
using namespace std;

int n=100;
int m,s,G[MAXV][MAXV],MAP[MAXV][MAXV];//存储坐标系每个点的编号
double  d[MAXV];
int pre[MAXV];
bool vis[MAXV] = {false};
int path[10000],path_num=0,ob_num=0;
xys xy[100];
int obid[1000];


void init(int span){
		int num=0;
	for(int i=0;i<span;i++){//初始化顶点编号
		for(int j=0;j<span;j++){
			xy[num].x=i;
			xy[num].y=j;
			MAP[i][j]=num++;
		}
	}

		for(int i=0;i<span;i++){

			for(int j=0;j<span;j++){

				if(i==0){
					if(j==0){
						int s = MAP[i][j];
						G[s][MAP[i+1][j]]=1;
						G[s][MAP[i][j+1]]=1;
						G[s][MAP[i+1][j+1]]=1.414;
					}else if (j==span-1){
						int s = MAP[i][j];
						G[s][MAP[i+1][j]]=1;
						G[s][MAP[i][j-1]]=1;
						G[s][MAP[i+1][j-1]]=1.414;
					}else{
						int s = MAP[i][j];
						G[s][MAP[i+1][j]]=1;
						G[s][MAP[i][j-1]]=1;
						G[s][MAP[i][j+1]]=1;
						G[s][MAP[i+1][j-1]]=1.414;
						G[s][MAP[i+1][j+1]]=1.414;
					}
				}else if(i==span-1){
					if(j==0){
						int s = MAP[i][j];
						G[s][MAP[i-1][j]]=1;
						G[s][MAP[i][j+1]]=1;
						G[s][MAP[i-1][j+1]]=1.414;
					}else if (j==span-1){
						int s = MAP[i][j];
						G[s][MAP[i-1][j]]=1;
						G[s][MAP[i][j-1]]=1;
						G[s][MAP[i-1][j-1]]=1.414;
					}else{
						int s = MAP[i][j];
						G[s][MAP[i-1][j]]=1;
						G[s][MAP[i][j-1]]=1;
						G[s][MAP[i][j+1]]=1;
							G[s][MAP[i-1][j-1]]=1.414;
						G[s][MAP[i-1][j+1]]=1.414;
					}

				}
				else{
					if(j==0){
						int s = MAP[i][j];
						G[s][MAP[i-1][j]]=1;
						G[s][MAP[i+1][j]]=1;
						G[s][MAP[i][j+1]]=1;
							G[s][MAP[i-1][j+1]]=1.414;
						G[s][MAP[i+1][j+1]]=1.414;
					}else if (j==span-1){
						int s = MAP[i][j];
						G[s][MAP[i-1][j]]=1;
						G[s][MAP[i+1][j]]=1;
						G[s][MAP[i][j-1]]=1;
							G[s][MAP[i-1][j-1]]=1.414;
						G[s][MAP[i+1][j-1]]=1.414;
					}else{
						int s = MAP[i][j];
						G[s][MAP[i-1][j]]=1;
						G[s][MAP[i+1][j]]=1;
						G[s][MAP[i][j-1]]=1;
						G[s][MAP[i][j+1]]=1;
							G[s][MAP[i-1][j-1]]=1.414;
						G[s][MAP[i+1][j+1]]=1.414;
						G[s][MAP[i-1][j+1]]=1.414;
						G[s][MAP[i+1][j-1]]=1.414;
					}
				}

			}
	}
}

void Dikstra(int s){
	fill(d,d+MAXV,INF);
	for(int i=0;i<n;i++)
		pre[i]=i;
	d[s]=0;
	for(int i=0;i<n;i++){
		int u = -1,MIN = INF;
		for(int j=0;j<n;j++){
			if(vis[j]==false&&d[j]<MIN){
				u=j;
				MIN=d[j];
			}
		}
		if(u==-1)return;
		vis[u] = true;
		for(int v =0;v<n;v++){
			if(vis[v] == false &&G[u][v]!=INF && d[u]+G[u][v]<d[v]){
				d[v] = d[u] + G[u][v];
				pre[v]=u;
			}
		}
	}
}

void DFS(int s,int v){
	if(v==s){
		path[path_num++]=v;
		return;
	}
	DFS(s,pre[v]);
	path[path_num++]=v;
}

void obstacle(int span){

	
	printf("please input the num of obtacles:\n");
	scanf("%d",&ob_num);
	srand((unsigned)time(NULL));
	for(int i=0;i<ob_num;i++){
		printf("please input the id of obtacle:\n");
		int temp;
		
		temp=rand()%100;
		printf("%d\n",temp);
		//scanf("%d",&temp);
		obid[i]=temp;
	if(temp+span<n){//下边还有
		G[temp][temp+span]=INF;
			if(temp+span>0)//左下还有
				G[temp][temp+span-1]=INF;
			if(temp+span<n-1)//右下还有
				G[temp][temp+span+1]=INF;
	}
	if(temp-span>=0){//上边还有
		G[temp][temp-span]=INF;
		if(temp-span>0)//左上还有
				G[temp][temp-span-1]=INF;
			if(temp-span<n-1)//右上还有
				G[temp][temp-span+1]=INF;

	}
	if(temp+1<n){//右边还有
		G[temp][temp+1]=INF;
			if(temp-span<n-1)//右上还有
				G[temp][temp-span+1]=INF;
			if(temp+span<n-1)//右下还有
				G[temp][temp+span+1]=INF;

	}
	if(temp-1>=0){//左边还有
		G[temp][temp-1]=INF;
			if(temp-span>0)//左上还有
				G[temp][temp-span-1]=INF;
			if(temp+span>0)//左下还有
				G[temp][temp+span-1]=INF;

	}

}
}