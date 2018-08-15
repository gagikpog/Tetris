#include "Game.h"
#include "lib/GluiText.h"

int WndW = 450+150,WndH = 810;
bool pause = false;

using namespace std;

void Timer(int t = 0);

Game game(10,18);
Game window(5,5);
GLUI::Glui_Text text;

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    game.Print();
    window.Print();
    GLUI::Gl_Print_Rectangle(WndW - 150, WndH - 150,140,140,GLUI::Gray);
    text.glText(WndW - 140, WndH - 30,"Score : " + to_string(game.Score),GLUI::White);
    text.glText(WndW - 140, WndH - 60,"Lines : " + to_string(game.Lines),GLUI::White);
    text.glText(WndW - 140, WndH - 90,"Level : " + to_string(game.Level),GLUI::White);
    glutSwapBuffers();
}

void init()
{   
    srand(time(NULL));
    game.LoadBlocks("blocksMap.map");
    game.InitFrame(10,10,WndW-20-150,WndH-20);
    game.setBckgColor(GLUI::Glui_Colornum::Black);
    window.LoadBlocks("blocksMap.map");
    window.InitFrame(WndW - 150, WndH - 300,140,140);
    window.setBckgColor(GLUI::Glui_Colornum::Black);
    window.NextBlockID = game.NextBlockID;
    window.NewGame();
    window.Next();
    Timer();
}
void Keys(BYTE key,int ax,int ay)
{
    if(key == 27)
        exit(0);
    if(key == 'p'|| key == 'P')
        pause = !pause;
    if(!pause)
        game.KeyboardFunc(key,ax,WndH-ay);
}

void Keys(int key,int ax,int ay)
{
    if(!pause)
        game.SpecialFunc(key,ax,WndH - ay);
}

void Timer(int t)
{
    glutPostRedisplay();
    if(!pause)
    {
        if(!game.Next())
        {   
            window.NextBlockID = game.NextBlockID;
            window.NewGame();
            window.Next();
        }
    }
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