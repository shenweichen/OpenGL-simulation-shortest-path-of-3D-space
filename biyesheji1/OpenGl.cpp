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
static GLfloat axis = 5.0f;//������볤��
const GLfloat R = 0.5;  
const GLfloat Pi = 3.1415926536f;  
int strip = 10;
GLfloat xRotAngle=0.0f;  //��x����ת�Ƕ�  
GLfloat yRotAngle=0.0f;  //��x����ת�Ƕ�
double dLastX=0.0,dLastY=0.0;
int ithpath=0;
int nRange,nStartPoint,nEndPoint;
bool initIsTrue=true;

void init(void){
	
	axis=(double)nRange/2;
	GLfloat mat_specular[]={1.0,1.0,1.0,1.0};//����ľ��������ɫ
	GLfloat mat_shininess[]={50.0};//����Ĺ����
	GLfloat light_position []={1.0,1.0,1.0,0.0};//��Դλ�õ�����
	GLfloat white_light[]={1.0,1.0,1.0,1.0};//���ɢ��ǿ��
	GLfloat lmodel_ambient []={0.1,0.1,0.1,1.0};//ȫ�ֻ������RGBAǿ��

     glClearColor(1.0,1.0,1.0,0.0);
     glShadeModel(GL_SMOOTH);//
	 glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);//ָ������ľ��������ɫp.140
	 glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);//ָ������Ĺ����
	 glLightfv(GL_LIGHT0,GL_POSITION,light_position);//ָ����Դλ�õ�����
	 glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);//ָ�����ɢ��ǿ��
	 glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);//ָ����ľ���ǿ��
	 glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);//ָ��ȫ�ֻ������ǿ��
	 
	 glColorMaterial(GL_FRONT,GL_DIFFUSE); //���������ɫ
	 glEnable(GL_COLOR_MATERIAL); 

	 glEnable(GL_LIGHTING);//���ù���p.140
	 glEnable(GL_LIGHT0);//���ù�Դ
	 glEnable(GL_DEPTH_TEST);
	 
	 
}

void display(){
     glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	 glPushMatrix();     //��ͼ�任  p.81
	 //����ϵ��x����תxRotAngle  
    glRotatef(xRotAngle,1.0f,0.0f,0.0f);    
	//����ϵ��y����תyRotAngle  
    glRotatef(yRotAngle,0.0f,1.0f,0.0f);  
	    //����ƽ������  
    glEnable(GL_POINT_SMOOTH);  
    glHint(GL_POINT_SMOOTH,GL_NICEST);  
    glEnable(GL_LINE_SMOOTH);  
    glHint(GL_LINE_SMOOTH,GL_NICEST);  
    glEnable(GL_POLYGON_SMOOTH); 
    glHint(GL_POLYGON_SMOOTH,GL_NICEST); 
	//��ɫ��������ϵ  
    glColor3f(0.0f,0.0f,1.0f);  //��ʼλ��
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
	 glColor3f(0.0,1.0,1.0);//���ƻ���������λ��
	 glTranslatef(xspin-axis,yspin-axis,zspin);//��ͼ��ģ�ͱ任����  p.84  p.87
	 glutSolidSphere(R,strip,strip);//����ʵ����
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
	  glColor3f(1.0,1.0,0.0);//�����н�·��
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

//���ڴ�С�仯�ص�����  
void changeSize(GLint w,GLint h){  
    //������  
    GLfloat ratio;  
    //��������ϵΪx(-100.0f,100.0f)��y(-100.0f,100.0f)��z(-100.0f,100.0f)  
    GLfloat coordinatesize=axis*2;  
    //���ڿ��Ϊ��ֱ�ӷ���  
    if((w==0)||(h==0))  
        return;  
    //�����ӿںʹ��ڴ�Сһ��  
    glViewport(0,0,w,h);  
    //��ͶӰ����Ӧ�����ľ������  
    glMatrixMode(GL_PROJECTION);  
    //���õ�ǰָ���ľ���Ϊ��λ����  
    glLoadIdentity();  
    ratio=(GLfloat)w/(GLfloat)h;  
    //����ͶӰ  
    if(w<h)  
        glOrtho(-coordinatesize,coordinatesize,-coordinatesize/ratio,coordinatesize/ratio,-coordinatesize,coordinatesize);  
    else  
        glOrtho(-coordinatesize*ratio,coordinatesize*ratio,-coordinatesize,coordinatesize,-coordinatesize,coordinatesize);  
    //��ģ����ͼ�����ջӦ�����ľ������  
    glMatrixMode(GL_MODELVIEW);  
    //���õ�ǰָ���ľ���Ϊ��λ����  
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

void specialKey(int key,int x,int y){//�������봦����  
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
    //���»���  
    glutPostRedisplay();  
}  


 int main(int argc, char  **argv)
{
	printf("�������ͼ��ģn ��ģΪn*n:\n");
	scanf("%d",&nRange);
	while(nRange<2){
			printf("����\n�����������ͼ��ģn ��ģΪn*n:\n");
	scanf("%d",&nRange);
	}
	int max=nRange*nRange-1;
	printf("�����������յ��� ��ΧΪ0~%d:\n",max);
	scanf("%d %d",&nStartPoint,&nEndPoint);
	while(nStartPoint<0||nStartPoint>max||nEndPoint<0||nEndPoint>max||nStartPoint==nEndPoint){
	printf("�����ʽ����ȷ�������������� ��Χ0~%d:\n",max);
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
		printf("���·������Ϊ%.3lf\n",d[nEndPoint]);

	//--------------
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);//˫���壬
     glutInitWindowSize(700,700);
     glutInitWindowPosition(100,100);
     glutCreateWindow(argv[0]);
     init();
     glutDisplayFunc(display);
     glutReshapeFunc(changeSize);//Ĭ��Ϊreshape
     glutMouseFunc(mouse);
	 glutSpecialFunc(specialKey);  //�������봦��ص�����

     glutMainLoop();
	 system("pause");
     return 0;
}