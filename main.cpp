#include "Game.h"

int WndW = 450,WndH = 810;

using namespace std;

void Timer(int t = 0);

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
    game.setBckgColor(GLUI::Glui_Colornum::Black);
    srand(time(NULL));
    Timer();
}
void Keys(BYTE key,int ax,int ay)
{
    if(key == 27)
        exit(0);
}

void Keys(int key,int ax,int ay)
{
    game.SpecialFunc(key,ax,WndH - ay);
}

void Timer(int t)
{
    glutPostRedisplay();
    game.Next();
    glutTimerFunc(game.Speed,Timer,0);
}


int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(10,10);
    glutInitWindowSize(WndW,WndH);
    glutCreateWindow("Tetris");
    glClearColor(0,0.5,0.5,1);

    gluOrtho2D(0,WndW,0,WndH);
    init();
    glutKeyboardFunc(Keys);
    glutSpecialFunc(Keys);
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}