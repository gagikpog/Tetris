#include <iostream>
#include <GL/freeglut.h>

int WndW = 500,WndH = 800;

using namespace std;

void Display()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    glutSwapBuffers();
}


int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(10,10);
    glutInitWindowSize(WndW,WndH);
    glutCreateWindow("Tetris");


    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}