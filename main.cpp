#include "Tetris.h"

int WndW = 500,WndH = 800;

using namespace std;

Game game(50,80);

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
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}