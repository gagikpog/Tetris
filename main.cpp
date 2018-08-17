#include "Game.h"
#include "lib/GluiText.h"
#include "lib/ConfigINI.h"

int WndW = 450+150,WndH = 810;
bool pause = false;

using namespace std;

void Timer(int t = 0);

Game game(10,18);
Game window(5,5);
GLUI::Glui_Text text;
ConfigINI config("tetris.config");
//game settings
GLUI::Glui_Color BackgroundColor(GLUI::Black);
GLUI::Glui_Color TextColor(GLUI::White);
string blocksColorPath = "blocksColor.txt";
string blocksPath = "blocksMap.map";
//

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    GLUI::Gl_Print_Rectangle(0,0,WndW,WndH,BackgroundColor,BackgroundColor);
    game.Print();
    window.Print();
    GLUI::Gl_Print_Rectangle(WndW - 150, WndH - 150,140,140,GLUI::Glui_Color(50,50,50,100));
    text.glText(WndW - 140, WndH - 30,"Score : " + to_string(game.Score),TextColor);
    text.glText(WndW - 140, WndH - 60,"Lines : " + to_string(game.Lines),TextColor);
    text.glText(WndW - 140, WndH - 90,"Level : " + to_string(game.Level),TextColor);
    glutSwapBuffers();
}

void readConfig()
{
    //add all colors to the config
    config.addNewOption("Color","background",BackgroundColor.getUInt());
    config.addNewOption("Color","text",TextColor.getUInt());
    config.addNewOption("Color","game",game.gatBckgColor().getUInt());
    //add resource files path to the config
    config.addNewOption("Path","blocksColor",blocksColorPath);
    config.addNewOption("Path","blocks",blocksPath);

    //read colors from config
    BackgroundColor.setUInt(config.getOptionToUInt("Color","background"));
    TextColor.setUInt(config.getOptionToUInt("Color","text"));
    game.setBckgColor(GLUI::Glui_Color::UIntToColor(config.getOptionToUInt("Color","game")));
    window.setBckgColor(game.gatBckgColor());
    //read paths from config
    blocksColorPath = config.getOptionToString("Path","blocksColor");
    blocksPath = config.getOptionToString("Path","blocks");
}

void init()
{
    readConfig();
    srand(time(NULL));
    //Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    game.LoadBlocksFromFile(blocksPath);
    game.LoadBlocksColorsFromFile(blocksColorPath);
    game.InitFrame(10,10,WndW-20-150,WndH-20);
    window.LoadBlocksFromFile(blocksPath);
    window.LoadBlocksColorsFromFile(blocksColorPath);
    window.InitFrame(WndW - 150, WndH - 300,140,140);
    window.NextBlockID = game.NextBlockID;
    window.NextBlockColorID = game.NextBlockColorID;
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
            window.NextBlockColorID = game.NextBlockColorID;
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