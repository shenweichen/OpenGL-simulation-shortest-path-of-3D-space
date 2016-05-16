#include <GL/glut.h>

void myDisplay(void)

{

     glClear(GL_COLOR_BUFFER_BIT);

     glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

     glFlush();

}

void coordinate_3d()
{
    GLfloat points[] = {
        0.0f, 0.0f, 0.0f,
        10.0f, 0.0f, 0.0f, 
        0.0f, 10.0f, 0.0f,
        0.0f, 0.0f, 10.0f
    };
 
    GLubyte coordinate_3d[] = {0,1,0,2,0,3};
 
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
     
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,points);
    glColor3f(1.0f,1.0f,1.0f);
 
    glLoadIdentity();
    gluLookAt(6.0,5.0,4.0,0.0,0.0,0.0,0.0,1.0,0.0);
    glDrawElements(GL_LINES,6,GL_UNSIGNED_BYTE,coordinate_3d);
 
    glFlush();
}

int main(int argc, char *argv[])

{

     glutInit(&argc, argv);

     glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

     glutInitWindowPosition(100, 100);

     glutInitWindowSize(400, 400);

     glutCreateWindow("第一个OpenGL程序");

     glutDisplayFunc(&myDisplay);

     glutMainLoop();
	 coordinate_3d();

     return 0;

}
