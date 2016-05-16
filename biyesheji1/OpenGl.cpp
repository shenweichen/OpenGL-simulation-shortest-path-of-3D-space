#include <GL/glut.h>
#include<cstdlib>
#include<cstdio>
#include<windows.h>
#include<algorithm>
#include "shortpath.h"
using namespace std;
static GLfloat xspin = 0.0;
static GLfloat yspin = 0.0;
static GLfloat zspin = -4.0f;
static GLfloat edge = 8.0f;
double dLastX=0.0,dLastY=0.0;
int ithpath=0;
int nRange,nStartPoint,nEndPoint;
bool initIsTrue=true;

const GLfloat R = 0.28;  
const GLfloat Pi = 3.1415926536f;  


void init(void){
     glClearColor(1.0,1.0,1.0,0.0);
     glShadeModel(GL_FLAT);
}

void display(){
		 double tempx,tempy;
		tempx=(double)xy[nStartPoint].x;
	  tempy=(double)xy[nStartPoint].y;
     glClear(GL_COLOR_BUFFER_BIT);
     glPushMatrix();
	 if(initIsTrue){
		 glTranslatef(xspin,yspin,zspin);
		initIsTrue=false;}
	 else
	 glTranslatef(xspin-(double)xy[nStartPoint].x,yspin-(double)xy[nStartPoint].y,0);
    
	 glColor3f(0.0,0.0,1.0);		
	 glTranslatef(tempx-2,tempy-2,zspin);
	 glutWireSphere(0.2,20,16);
     glPopMatrix();

	  glColor3f(1.0,0.0,0.0);
	  for(int i=0;i<nObstacleNum;i++){
		double ob_x=xy[nObstacleID[i]].x;
		double ob_y=xy[nObstacleID[i]].y;			
		//-----------------
		   glPushMatrix();
		  glTranslatef(ob_x-2,ob_y-2,zspin);
		 glutWireSphere(0.2,10,10);
		 glPopMatrix();
		 //-------------------
	 }


	  glColor3f(0.0,1.0,0.0);
	  tempx=(double)xy[nEndPoint].x;
	  tempy=(double)xy[nEndPoint].y;
	  //glRectf(tempx-0.3,tempy-0.3,tempx+0.3,tempy+0.3);
	     glPushMatrix();
		
		  glTranslatef(tempx-2,tempy-2,zspin);
		 glutSolidSphere(0.2,15,15);
		 glPopMatrix();

	
	  glutWireCube(edge);
     glutSwapBuffers();

}


void moveDisplay(void){
		double xtemp,ytemp;
		//printf("请输入移动的坐标\n");
	//	scanf("%lf %lf",&xtemp,&ytemp);
		xtemp=(double)xy[nPath[ithpath]].x;
		ytemp=(double)xy[nPath[ithpath++]].y;

		xspin=xtemp;
		yspin=ytemp;
/*	xspin+=(xtemp-dLastX);
    yspin+=(ytemp-dLastY);
	dLastX = xtemp;
	dLastY = ytemp;*/
	
	 Sleep(500);
     glutPostRedisplay();
}

void reshape(int w,int h){
     glViewport(0,0,(GLsizei)w,(GLsizei)h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
	 glFrustum(-1, 1, -1, 1, 1, 20);  
	// gluPerspective(60.0,(GLfloat)w/(GLfloat)h,100.0,1000.0);
    // glOrtho(0.0,(double)nRange,0.0,(double)nRange,-1.0,1.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
	 gluLookAt(0.0,0.0,11.0,0.0,0.0,0.0,0.0,1.0,0.0);//3D新增


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
	printf("请输入地图规模n 规模为n*n:\n");
	scanf("%d",&nRange);
	//nRange=5;
	printf("请输入起点和终点编号:\n");
	scanf("%d %d",&nStartPoint,&nEndPoint);
	//nStartPoint=0;
	//nEndPoint=24;
	fill(G[0],G[0]+MAXV*MAXV,INF);
	init(nRange);	
	Obstacle(nRange,nStartPoint,nEndPoint);
	Dikstra(nStartPoint,nRange*nRange);
	DFS(nStartPoint,nEndPoint);
	for(int i=0;i<nPathNum;i++)
		printf("%d\n",nPath[i]);

	//--------------
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
     glutInitWindowSize(700,700);
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