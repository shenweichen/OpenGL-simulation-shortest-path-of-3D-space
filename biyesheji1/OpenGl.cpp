#include <GL/glut.h>
#include <stdlib.h>
#include<stdio.h>
#include<windows.h>
#include "shortpath.h"
#include<algorithm>
using namespace std;
static GLfloat xspin = 0.0;
static GLfloat yspin = 0.0;
double lastx=0.0,lasty=0.0;
int ithpath=0;
int end;
int t;
int map;
bool initflag=true;

const GLfloat R = 0.25;  
const GLfloat Pi = 3.1415926536f;  


void init(void){
     glClearColor(0.0,0.0,0.0,0.0);
     glShadeModel(GL_FLAT);
}

void display(){
		 double tempx,tempy;
	tempx=(double)xy[s].x;
	  tempy=(double)xy[s].y;
     glClear(GL_COLOR_BUFFER_BIT);
     glPushMatrix();
	 if(initflag){
		 glTranslatef(xspin,yspin,0.0);
		initflag=false;}
	 else
	 glTranslatef(xspin-(double)xy[s].x,yspin-(double)xy[s].y,0.0);
     glColor3f(0.0,0.0,1.0);
	// glRectf(tempx-0.3,tempy-0.3,tempx+0.3,tempy+0.3);
     glBegin(GL_POLYGON);
        
    for(int i=0; i<100; ++i)  
        glVertex2f(R*cos(2*Pi/100*i)+tempx, R*sin(2*Pi/100*i)+tempy);  
	glEnd();   

	
     glPopMatrix();
	        glColor3f(1.0,0.0,0.0);
	  for(int i=0;i<ob_num;i++){
		double ob_x=xy[obid[i]].x;
		double ob_y=xy[obid[i]].y;
	 glBegin(GL_POLYGON);
    for(int i=0; i<100; ++i)  
        glVertex2f(R*cos(2*Pi/100*i)+ob_x, R*sin(2*Pi/100*i)+ob_y);  
	glEnd();   
	 }
	  glColor3f(0.0,1.0,0.0);
	  tempx=(double)xy[t].x;
	  tempy=(double)xy[t].y;
	  glRectf(tempx-0.3,tempy-0.3,tempx+0.3,tempy+0.3);
     glutSwapBuffers();

}


void moveDisplay(void){
		double xtemp,ytemp;
		//printf("请输入移动的坐标\n");
	//	scanf("%lf %lf",&xtemp,&ytemp);
		xtemp=(double)xy[path[ithpath]].x;
		ytemp=(double)xy[path[ithpath++]].y;

	xspin+=(xtemp-lastx);
    yspin+=(ytemp-lasty);
	lastx = xtemp;
	lasty = ytemp;
	
	 Sleep(500);
     glutPostRedisplay();
}

void reshape(int w,int h){
     glViewport(0,0,(GLsizei)w,(GLsizei)h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
	 double mapd=(double)map;
     glOrtho(0.0,mapd,0.0,mapd,-1.0,1.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
}

void mouse(int button,int state,int x,int y){
     switch(button){
          case GLUT_LEFT_BUTTON:
               if(state==GLUT_DOWN)
                    glutIdleFunc(moveDisplay);
               break;
          case GLUT_RIGHT_BUTTON:
               if(state == GLUT_DOWN)
                    glutIdleFunc(NULL);
                    break;
          default:
               break;
     }
}


 int main(int argc, char  **argv)
{
	int end;
	//-----------
	printf("请输入地图规模n 规模为n*n:\n");
	scanf("%d",&map);
	//map=10;
	printf("请输入起点和终点编号:\n");
	scanf("%d%d",&s,&end);
	t=end;
	fill(G[0],G[0]+MAXV*MAXV,INF);
	init(map);	
	obstacle(map,end);
	Dikstra(s,map*map);
	DFS(s,end);
	for(int i=0;i<path_num;i++)
		printf("%d\n",path[i]);

	//----------
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
     glutInitWindowSize(500,500);
     glutInitWindowPosition(100,100);
     glutCreateWindow(argv[0]);
     init();
     glutDisplayFunc(display);
     glutReshapeFunc(reshape);
     glutMouseFunc(mouse);


     glutMainLoop();

	while(1);
     return 0;
}