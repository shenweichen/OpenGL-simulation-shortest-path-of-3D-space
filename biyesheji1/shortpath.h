
const int MAXV=1000 ;
const double INF=1000000.0 ;
extern int n;
extern int m,s,G[MAXV][MAXV],MAP[MAXV][MAXV];//存储坐标系每个点的编号
extern double  d[MAXV];
extern int pre[MAXV];
extern bool vis[MAXV] ;
extern int path[10000],path_num,ob_num;
extern struct xys{
int x,y;
}xy[100];

extern int obid[1000];

extern void init(int span);
extern void Dikstra(int s);
extern void DFS(int s,int v);
extern void obstacle(int span);