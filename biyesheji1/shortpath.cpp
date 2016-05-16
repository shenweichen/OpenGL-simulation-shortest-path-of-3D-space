#include<stdio.h>
#include"shortpath.h"
#include<algorithm>
#include<time.h>
using namespace std;
int n=100;
int m,s,G[MAXV][MAXV],MAP[MAXV][MAXV];//�洢����ϵÿ����ı��
double  d[MAXV];
int pre[MAXEDGE];
bool vis[MAXV] = {false};
int path[MAXEDGE],path_num=0,ob_num=0;
xys xy[MAXV];
int obid[1000];


void init(int map){
		int num=0;
	for(int i=0;i<map;i++){//��ʼ��������
		for(int j=0;j<map;j++){
			xy[num].x=i;
			xy[num].y=j;
			MAP[i][j]=num++;
		}
	}

		for(int i=0;i<map;i++){

			for(int j=0;j<map;j++){
					int s = MAP[i][j];
				if(i==0){
					if(j==0){
						G[s][MAP[i+1][j]]=1;
						G[s][MAP[i][j+1]]=1;
						G[s][MAP[i+1][j+1]]=1.414;
					}else if (j==map-1){
						G[s][MAP[i+1][j]]=1;
						G[s][MAP[i][j-1]]=1;
						G[s][MAP[i+1][j-1]]=1.414;
					}else{
						G[s][MAP[i+1][j]]=1;
						G[s][MAP[i][j-1]]=1;
						G[s][MAP[i][j+1]]=1;
						G[s][MAP[i+1][j-1]]=1.414;
						G[s][MAP[i+1][j+1]]=1.414;
					}
				}else if(i==map-1){
					if(j==0){
						G[s][MAP[i-1][j]]=1;
						G[s][MAP[i][j+1]]=1;
						G[s][MAP[i-1][j+1]]=1.414;
					}else if (j==map-1){
						G[s][MAP[i-1][j]]=1;
						G[s][MAP[i][j-1]]=1;
						G[s][MAP[i-1][j-1]]=1.414;
					}else{
						G[s][MAP[i-1][j]]=1;
						G[s][MAP[i][j-1]]=1;
						G[s][MAP[i][j+1]]=1;
							G[s][MAP[i-1][j-1]]=1.414;
						G[s][MAP[i-1][j+1]]=1.414;
					}

				}
				else{
					if(j==0){
						G[s][MAP[i-1][j]]=1;
						G[s][MAP[i+1][j]]=1;
						G[s][MAP[i][j+1]]=1;
							G[s][MAP[i-1][j+1]]=1.414;
						G[s][MAP[i+1][j+1]]=1.414;
					}else if (j==map-1){
						G[s][MAP[i-1][j]]=1;
						G[s][MAP[i+1][j]]=1;
						G[s][MAP[i][j-1]]=1;
							G[s][MAP[i-1][j-1]]=1.414;
						G[s][MAP[i+1][j-1]]=1.414;
					}else{
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

void Dikstra(int s,int numofvertex){
	fill(d,d+MAXV,INF);
	for(int i=0;i<MAXEDGE;i++)
		pre[i]=i;
	d[s]=0;
	for(int i=0;i<numofvertex;i++){
		int u = -1,MIN = INF;
		for(int j=0;j<numofvertex;j++){
			if(vis[j]==false&&d[j]<MIN){
				u=j;
				MIN=d[j];
			}
		}
		if(u==-1){
			printf("û��·������ͨ��\n");
			return;}
		vis[u] = true;
		for(int v =0;v<numofvertex;v++){
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

void obstacle(int map,int end){

	
	printf("�������ϰ������� obtacles:\n");
	scanf("%d",&ob_num);
	srand((unsigned)time(NULL));
	int total_vertex=map*map;
	for(int i=0;i<ob_num;i++){
		//printf("please input the id of obtacle:\n");
		int temp;
		//scanf("%d",&temp);
		temp=rand()%total_vertex;
		if(temp==s||temp==end){
			i--;
			continue;
		}
		//printf("%d\n",temp);
		
		obid[i]=temp;
	if(temp+map<total_vertex){//�±߻���
		G[temp][temp+map]=INF;
			if(temp+map>0)//���»���
				G[temp][temp+map-1]=INF;
			if(temp+map<total_vertex-1)//���»���
				G[temp][temp+map+1]=INF;
	}
	if(temp-map>=0){//�ϱ߻���
		G[temp][temp-map]=INF;
		if(temp-map>0)//���ϻ���
				G[temp][temp-map-1]=INF;
			if(temp-map<n-1)//���ϻ���
				G[temp][temp-map+1]=INF;

	}
	if(temp+1<total_vertex){//�ұ߻���
		G[temp][temp+1]=INF;
			if(temp-map<total_vertex-1)//���ϻ���
				G[temp][temp-map+1]=INF;
			if(temp+map<total_vertex-1)//���»���
				G[temp][temp+map+1]=INF;

	}
	if(temp-1>=0){//��߻���
		G[temp][temp-1]=INF;
			if(temp-map>0)//���ϻ���
				G[temp][temp-map-1]=INF;
			if(temp+map>0)//���»���
				G[temp][temp+map-1]=INF;

	}

}
}


