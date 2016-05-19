
const int MAXV=10000 ;
const int MAXEDGE=8*MAXV;
const double INF=1000000.0 ;
extern double G[MAXV][MAXV],d[MAXV];
extern int pre[MAXEDGE];
extern bool IsVisited[MAXV] ,flag;
extern int nPath[MAXEDGE],nPathNum,nObstacleID[1000],nObstacleNum;
extern struct COORDINATE{
int x,y;
}xy[MAXV];


extern void init(int map);
extern void Dikstra(int s,int nVertexNum);
extern void DFS(int s,int v);
extern void Obstacle(int span,int s,int end);