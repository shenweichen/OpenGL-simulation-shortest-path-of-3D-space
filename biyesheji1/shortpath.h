
const int MAXV=10000 ;
const int MAXEDGE=8*MAXV;
const double INF=1000000.0 ;
extern int s,G[MAXV][MAXV];
extern double  d[MAXV];
extern int pre[MAXEDGE];
extern bool IsVisited[MAXV] ;
extern int nPath[MAXEDGE],nPathNum,nObstacleNum;
extern struct COORDINATE{
int x,y;
}xy[MAXV];

extern int nObstacleID[1000];

extern void init(int map);
extern void Dikstra(int s,int numofvertex);
extern void DFS(int s,int v);
extern void obstacle(int span,int end);