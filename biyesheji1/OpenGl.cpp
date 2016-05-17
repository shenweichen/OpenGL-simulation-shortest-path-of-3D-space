#include <GL/glut.h>
#include<cstdlib>
#include<cstdio>
#include<windows.h>
#include<algorithm>
#include "shortpath.h"
using namespace std;
static GLfloat xspin = 0.0;
static GLfloat yspin = 0.0;
static GLfloat zspin = 0.0f;
static GLfloat axis = 5.0f;//坐标轴半长度
const GLfloat R = 0.4;  
const GLfloat Pi = 3.1415926536f;  
GLfloat xRotAngle=0.0f;  //绕x轴旋转角度  
GLfloat yRotAngle=0.0f;  //绕x轴旋转角度
double dLastX=0.0,dLastY=0.0;
int ithpath=0;
int nRange,nStartPoint,nEndPoint;
bool initIsTrue=true;

void init(void){
     glClearColor(0.0,0.0,0.0,0.0);
     glShadeModel(GL_FLAT);
}

void display(){
		 double tempx,tempy;
		tempx=(double)xy[nStartPoint].x;
	  tempy=(double)xy[nStartPoint].y;
     glClear(GL_COLOR_BUFFER_BIT);
	 glPushMatrix();
	 //坐标系绕x轴旋转xRotAngle  
    glRotatef(xRotAngle,1.0f,0.0f,0.0f);    
	//坐标系绕y轴旋转yRotAngle  
    glRotatef(yRotAngle,0.0f,1.0f,0.0f);  
	    //进行平滑处理　  
    glEnable(GL_POINT_SMOOTH);  
    glHint(GL_POINT_SMOOTH,GL_NICEST);  
    glEnable(GL_LINE_SMOOTH);  
    glHint(GL_LINE_SMOOTH,GL_NICEST);  
    glEnable(GL_POLYGON_SMOOTH);  
    glHint(GL_POLYGON_SMOOTH,GL_NICEST); 

	//白色绘制坐标系  
    glColor3f(1.0f,1.0f,1.0f);  
    glBegin(GL_LINES);  
        glVertex3f(-axis,0.0f,0.0f);  
        glVertex3f(axis,0.0f,0.0f);  
        glVertex3f(0.0f,-axis,0.0f);  
        glVertex3f(0.0f,axis,0.0f);  
        glVertex3f(0.0f,0.0f,-axis);  
        glVertex3f(0.0f,0.0f,axis);  
    glEnd();  




     glPushMatrix();
	 if(initIsTrue){
		 glTranslatef(xspin,yspin,zspin);
		initIsTrue=false;}
	 else;
	 glTranslatef(xspin-(double)xy[nStartPoint].x,yspin-(double)xy[nStartPoint].y,0);
    
	 glColor3f(0.0,0.0,1.0);		
	 glTranslatef(tempx-axis,tempy-axis,zspin);
	 glutWireSphere(R,10,10);
     glPopMatrix();

	  glColor3f(1.0,0.0,0.0);
	  for(int i=0;i<nObstacleNum;i++){
		double ob_x=xy[nObstacleID[i]].x;
		double ob_y=xy[nObstacleID[i]].y;			
		//-----------------
		   glPushMatrix();
		  glTranslatef(ob_x-axis,ob_y-axis,zspin);
		 glutWireSphere(R,10,10);
		 glPopMatrix();
		 //-------------------
	 }


	  glColor3f(0.0,1.0,0.0);
	  tempx=(double)xy[nEndPoint].x;
	  tempy=(double)xy[nEndPoint].y;
	  //glRectf(tempx-0.3,tempy-0.3,tempx+0.3,tempy+0.3);
	     glPushMatrix();
		
		  glTranslatef(tempx-axis,tempy-axis,zspin);
		 glutSolidSphere(R,15,15);
		 glPopMatrix();

	
	  glutWireCube(axis*2);
	  	glPopMatrix();  
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

//窗口大小变化回调函数  
void changeSize(GLint w,GLint h){  
    //横宽比率  
    GLfloat ratio;  
    //设置坐标系为x(-100.0f,100.0f)、y(-100.0f,100.0f)、z(-100.0f,100.0f)  
    GLfloat coordinatesize=axis*2;  
    //窗口宽高为零直接返回  
    if((w==0)||(h==0))  
        return;  
    //设置视口和窗口大小一致  
    glViewport(0,0,w,h);  
    //对投影矩阵应用随后的矩阵操作  
    glMatrixMode(GL_PROJECTION);  
    //重置当前指定的矩阵为单位矩阵　  
    glLoadIdentity();  
    ratio=(GLfloat)w/(GLfloat)h;  
    //正交投影  
    if(w<h)  
        glOrtho(-coordinatesize,coordinatesize,-coordinatesize/ratio,coordinatesize/ratio,-coordinatesize,coordinatesize);  
    else  
        glOrtho(-coordinatesize*ratio,coordinatesize*ratio,-coordinatesize,coordinatesize,-coordinatesize,coordinatesize);  
    //对模型视图矩阵堆栈应用随后的矩阵操作  
    glMatrixMode(GL_MODELVIEW);  
    //重置当前指定的矩阵为单位矩阵　  
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

void specialKey(int key,int x,int y){//按键输入处理函数  
    if(key==GLUT_KEY_UP){  
        xRotAngle-=5.0f;  
    }  
    else if(key==GLUT_KEY_DOWN){  
        xRotAngle+=5.0f;  
    }  
    else if(key==GLUT_KEY_LEFT){  
        yRotAngle-=5.0f;  
    }  
    else if(key==GLUT_KEY_RIGHT){  
        yRotAngle+=5.0f;  
    }  
    //重新绘制  
    glutPostRedisplay();  
}  


 int main(int argc, char  **argv)
{
	printf("请输入地图规模n 规模为n*n:\n");
	//scanf("%d",&nRange);
	nRange=10;
	printf("请输入起点和终点编号:\n");
	//scanf("%d %d",&nStartPoint,&nEndPoint);
	nStartPoint=0;
	nEndPoint=99;
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
     glutReshapeFunc(changeSize);//默认为reshape
     glutMouseFunc(mouse);
	 glutSpecialFunc(specialKey);  //按键输入处理回调函数

     glutMainLoop();

     return 0;
}