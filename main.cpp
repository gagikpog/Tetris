#include "Tetris.h"

int WndW = 450,WndH = 810;

using namespace std;

Game game(10,18);

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    game.Print();

    glutSwapBuffers();
}
void init()
{
    game.InitFrame(10,10,WndW-20,WndH-20);
}
void Keys(BYTE key,int ax,int ay)
{
    if(key == 27)
        exit(0);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(10,10);
    glutInitWindowSize(WndW,WndH);
    glutCreateWindow("Tetris");
    glClearColor(1,1,1,1);

    gluOrtho2D(0,WndW,0,WndH);
    init();
    glutKeyboardFunc(Keys);
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}