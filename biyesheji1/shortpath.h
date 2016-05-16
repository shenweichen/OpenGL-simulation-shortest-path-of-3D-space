
const int MAXV=10000 ;
const int MAXEDGE=8*MAXV;
const double INF=1000000.0 ;
extern int n;
extern int m,s,G[MAXV][MAXV],MAP[MAXV][MAXV];//存储坐标系每个点的编号
extern double  d[MAXV];
extern int pre[MAXEDGE];
extern bool vis[MAXV] ;
extern int path[MAXEDGE],path_num,ob_num;
extern struct xys{
int x,y;
}xy[MAXV];

extern int obid[1000];

extern void init(int map);
extern void Dikstra(int s,int numofvertex);
extern void DFS(int s,int v);
extern void obstacle(int span,int end);