#include<stdio.h>
#include"shortpath.h"
#include<algorithm>
#include<time.h>
using namespace std;
double G[MAXV][MAXV],d[MAXV];
int pre[MAXEDGE];
bool IsVisited[MAXV] = {false},flag=true;
int nPath[MAXEDGE],nPathNum=0,nObstacleNum=0;
COORDINATE xy[MAXV];
int nObstacleID[1000];

int Hash(int x,int y,int range){//���ָ������Ķ�����
	return x*range+y;
}


void init(int nRange){
		int num=0;
	for(int i=0;i<nRange;i++){//��ʼ��ָ����ŵĵ������
		for(int j=0;j<nRange;j++,num++){
			xy[num].x=i;
			xy[num].y=j;
		}
	}
		for(int i=0;i<nRange;i++){
			for(int j=0;j<nRange;j++){
					int s = Hash(i,j,nRange);	
				if(i==0){
					if(j==0){
						G[s][s+nRange]=1;
						G[s][s+1]=1;
						G[s][s+nRange+1]=1.414;
					}else if (j==nRange-1){
						G[s][s+nRange]=1;
						G[s][s-1]=1;
						G[s][s+nRange-1]=1.414;
					}else{
						G[s][s+nRange]=1;
						G[s][s-1]=1;
						G[s][s+1]=1;
						G[s][s+nRange-1]=1.414;
						G[s][s+nRange+1]=1.414;
					}
				}else if(i==nRange-1){
					if(j==0){
						G[s][s-nRange]=1;
						G[s][s+1]=1;
						G[s][s-nRange+1]=1.414;
					}else if (j==nRange-1){
						G[s][s-nRange]=1;
						G[s][s-1]=1;
						G[s][s-nRange-1]=1.414;
					}else{
						G[s][s-nRange]=1;
						G[s][s-1]=1;
						G[s][s+1]=1;
						G[s][s-nRange-1]=1.414;
						G[s][s-nRange+1]=1.414;
					}
				}
				else{
					if(j==0){
						G[s][s-nRange]=1;
						G[s][s+nRange]=1;
						G[s][s+1]=1;
						G[s][s-nRange+1]=1.414;
						G[s][s+nRange+1]=1.414;
					}else if (j==nRange-1){
						G[s][s-nRange]=1;
						G[s][s+nRange]=1;
						G[s][s-1]=1;
						G[s][s-nRange-1]=1.414;
						G[s][s+nRange-1]=1.414;
					}else{
						G[s][s-nRange]=1;
						G[s][s+nRange]=1;
						G[s][s-1]=1;
						G[s][s+1]=1;
						G[s][s-nRange-1]=1.414;
						G[s][s+nRange+1]=1.414;
						G[s][s-nRange+1]=1.414;
						G[s][s+nRange-1]=1.414;
					}
				}
			}
	}
}

void Dikstra(int s,int nVertexNum){
	fill(d,d+MAXV,INF);
	for(int i=0;i<MAXEDGE;i++)
		pre[i]=i;
	d[s]=0;
	for(int i=0;i<nVertexNum;i++){
		int u = -1;
		double MIN=INF;
		for(int j=0;j<nVertexNum;j++){
			if(IsVisited[j]==false&&d[j]<MIN){
				u=j;
				MIN=d[j];
			}
		}
		if(u==-1){
			printf("û��·������ͨ��\n");
			flag = false;
			return;}
		IsVisited[u] = true;
		for(int v =0;v<nVertexNum;v++){
			if(IsVisited[v] == false &&G[u][v]!=INF && d[u]+G[u][v]<d[v]){
				d[v] = d[u] + G[u][v];
				pre[v]=u;
			}
		}
	}
}

void DFS(int s,int v){
	if(v==s){
		nPath[nPathNum++]=v;
		return;
	}
	DFS(s,pre[v]);
	nPath[nPathNum++]=v;
}

void Obstacle(int nRange,int s,int end){

	
	printf("�������ϰ�������0~%d:\n",nRange*nRange);
	scanf("%d",&nObstacleNum);
	while(nObstacleNum>=nRange*nRange||nObstacleNum<0){
	printf("���������������ϰ�������0~%d:\n",nRange*nRange);
		scanf("%d",&nObstacleNum);
	}
	srand((unsigned)time(NULL));
	int total_vertex=nRange*nRange;
	for(int i=0;i<nObstacleNum;i++){
		//printf("please input the id of obtacle:\n");
		int temp;
		//scanf("%d",&temp);
		temp=rand()%total_vertex;
		if(temp==s||temp==end){//������ɵ��������յ㣬������
			i--;
			continue;}
		else{
		nObstacleID[i]=temp;
		//printf("%d\n",temp);
		
		
	if(temp+nRange<total_vertex){//�±߻���
		G[temp][temp+nRange]=INF;
			if(temp+nRange>0)//���»���
				G[temp][temp+nRange-1]=INF;
			if(temp+nRange<total_vertex-1)//���»���
				G[temp][temp+nRange+1]=INF;
	}
	if(temp-nRange>=0){//�ϱ߻���
		G[temp][temp-nRange]=INF;
		if(temp-nRange>0)//���ϻ���
				G[temp][temp-nRange-1]=INF;
			if(temp-nRange<total_vertex-1)//���ϻ���
				G[temp][temp-nRange+1]=INF;

	}
	if(temp+1<total_vertex){//�ұ߻���
		G[temp][temp+1]=INF;
			if(temp-nRange<total_vertex-1)//���ϻ���
				G[temp][temp-nRange+1]=INF;
			if(temp+nRange<total_vertex-1)//���»���
				G[temp][temp+nRange+1]=INF;

	}
	if(temp-1>=0){//��߻���
		G[temp][temp-1]=INF;
			if(temp-nRange>0)//���ϻ���
				G[temp][temp-nRange-1]=INF;
			if(temp+nRange>0)//���»���
				G[temp][temp+nRange-1]=INF;

	}
		}
}
}


