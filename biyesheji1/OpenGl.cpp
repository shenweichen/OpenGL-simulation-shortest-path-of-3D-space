#include <GL/glut.h>
#include<cstdlib>
#include<cstdio>
#include<windows.h>
#include<algorithm>
#include "shortpath.h"
using namespace std;
static GLfloat xspin = 0.0f;
static GLfloat yspin = 0.0f;
static GLfloat zspin = 0.0f;
static GLfloat axis = 5.0f;//坐标轴半长度
const GLfloat R = 0.5;  
const GLfloat Pi = 3.1415926536f;  
int strip = 10;
GLfloat xRotAngle=0.0f;  //绕x轴旋转角度  
GLfloat yRotAngle=0.0f;  //绕x轴旋转角度
double dLastX=0.0,dLastY=0.0;
int ithpath=0;
int nRange,nStartPoint,nEndPoint;
bool initIsTrue=true;

void init(void){
	
	axis=(double)nRange/2;
	GLfloat mat_specular[]={1.0,1.0,1.0,1.0};//物体的镜面材料颜色
	GLfloat mat_shininess[]={50.0};//物体的光泽度
	GLfloat light_position []={1.0,1.0,1.0,0.0};//光源位置的坐标
	GLfloat white_light[]={1.0,1.0,1.0,1.0};//光的散射强度
	GLfloat lmodel_ambient []={0.1,0.1,0.1,1.0};//全局环境光的RGBA强度

     glClearColor(1.0,1.0,1.0,0.0);
     glShadeModel(GL_SMOOTH);//
	 glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);//指定物体的镜面材料颜色p.140
	 glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);//指定物体的光泽度
	 glLightfv(GL_LIGHT0,GL_POSITION,light_position);//指定光源位置的坐标
	 glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);//指定光的散射强度
	 glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);//指定光的镜面强度
	 glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);//指定全局环境光的强度
	 
	 glColorMaterial(GL_FRONT,GL_DIFFUSE); //允许材质颜色
	 glEnable(GL_COLOR_MATERIAL); 

	 glEnable(GL_LIGHTING);//启用光照p.140
	 glEnable(GL_LIGHT0);//启用光源
	 glEnable(GL_DEPTH_TEST);
	 
	 
}

void display(){
     glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	 glPushMatrix();     //视图变换  p.81
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
    glColor3f(0.0f,0.0f,1.0f);  //起始位置
    glBegin(GL_LINES);  
		glDisable(GL_COLOR_MATERIAL); 
        glVertex3f(-axis,0.0f,0.0f);  
        glVertex3f(axis,0.0f,0.0f);  
        glVertex3f(0.0f,-axis,0.0f);  
        glVertex3f(0.0f,axis,0.0f);  
        glVertex3f(0.0f,0.0f,-axis);  
        glVertex3f(0.0f,0.0f,axis);  
		glEnable(GL_COLOR_MATERIAL); 
    glEnd();  

     glPushMatrix();
	if(initIsTrue){
		xspin=(double)xy[nStartPoint].x;
		yspin=(double)xy[nStartPoint].y;
		initIsTrue=false;
	}
	 glColor3f(0.0,1.0,1.0);//绘制机器人所在位置
	 glTranslatef(xspin-axis,yspin-axis,zspin);//视图和模型变换函数  p.84  p.87
	 glutSolidSphere(R,strip,strip);//绘制实心球
     glPopMatrix();

	  glColor3f(1.0,0.0,1.0);
	  for(int i=0;i<nObstacleNum;i++){
		double ob_x=xy[nObstacleID[i]].x;
		double ob_y=xy[nObstacleID[i]].y;			
		//-----------------
		   glPushMatrix();
		  glTranslatef(ob_x-axis,ob_y-axis,zspin);
		 glutSolidSphere(R,strip,strip);
		 glPopMatrix();
		 //-------------------
	 }
	  glColor3f(1.0,1.0,0.0);//绘制行进路线
	  	  for(int i=0;i<nPathNum;i++){
		double ob_x=xy[ nPath[i]].x;
		double ob_y=xy[ nPath[i]].y;
		//-----------------
		   glPushMatrix();
		  glTranslatef(ob_x-axis,ob_y-axis,zspin);
		 glutSolidSphere(R*0.5,strip,strip);
		 glPopMatrix();
		 //-------------------
	 }



	  glColor3f(0.0,1.0,0.0);

	  //glRectf(tempx-0.3,tempy-0.3,tempx+0.3,tempy+0.3);
	     glPushMatrix();
		
		  glTranslatef((double)xy[nEndPoint].x-axis,(double)xy[nEndPoint].y-axis,zspin);
		 glutSolidSphere(R,strip,strip);
		 glPopMatrix();

	glDisable(GL_COLOR_MATERIAL); 

	  glutWireCube(axis*2);
	   glEnable(GL_COLOR_MATERIAL); 
	  	glPopMatrix();  
		glFlush();
     glutSwapBuffers();

}


void moveDisplay(void){
		xspin=(double)xy[nPath[ithpath]].x;
		yspin=(double)xy[nPath[ithpath++]].y;
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
	scanf("%d",&nRange);
	while(nRange<2){
			printf("错误！\n请重新输入地图规模n 规模为n*n:\n");
	scanf("%d",&nRange);
	}
	int max=nRange*nRange-1;
	printf("请输入起点和终点编号 范围为0~%d:\n",max);
	scanf("%d %d",&nStartPoint,&nEndPoint);
	while(nStartPoint<0||nStartPoint>max||nEndPoint<0||nEndPoint>max||nStartPoint==nEndPoint){
	printf("输入格式不正确，请重新输入编号 范围0~%d:\n",max);
	scanf("%d %d",&nStartPoint,&nEndPoint);
	}
	fill(G[0],G[0]+MAXV*MAXV,INF);
	init(nRange);	
	Obstacle(nRange,nStartPoint,nEndPoint);
	Dikstra(nStartPoint,nRange*nRange);
	if(flag==false){
		system("pause");
		return 0;}
	DFS(nStartPoint,nEndPoint);
		printf("最短路径长度为%.3lf\n",d[nEndPoint]);

	//--------------
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);//双缓冲，
     glutInitWindowSize(700,700);
     glutInitWindowPosition(100,100);
     glutCreateWindow(argv[0]);
     init();
     glutDisplayFunc(display);
     glutReshapeFunc(changeSize);//默认为reshape
     glutMouseFunc(mouse);
	 glutSpecialFunc(specialKey);  //按键输入处理回调函数

     glutMainLoop();
	 system("pause");
     return 0;
}