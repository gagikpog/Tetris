#include "Game.h"
#include "lib/GluiText.h"
#include "lib/ConfigINI.h"
#include "Sound.h"
#include "Label.h"

int WndW = 450+150,WndH = 810;
bool pause = false;
Sound gameSound, pauseSound, rotateSound, gameOverSound;
Label muzOffButton;
Label soundOffButton;

using namespace std;

void soundsOn(bool state);
void TimerDisplay(int t = 0);
void Timer(int t = 0);

Game game(10,18);
Game window(5,5);
GLUI::Glui_Text text;
ConfigINI config("tetris.config");
//game settings
GLUI::Glui_Color BackgroundColor(22,215,255);
GLUI::Glui_Color TextColor(GLUI::White);
//path
string blocksColorPath = "blocksColor.txt";
string blocksPath = "blocksMap.map";
string gameSoundPath = "Sound/sound.wav";
string pauseSoundPath  = "Sound/pause.wav";
string rotateSoundPath = "Sound/rotate.wav";
string gameOverSoundPath = "Sound/game over.wav";
//

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    GLUI::Gl_Print_Rectangle(0,0,WndW,WndH,BackgroundColor,BackgroundColor);
    game.Print();
    window.Print();
    GLUI::Gl_Print_Rectangle(WndW - 150, WndH -  40,140,30,GLUI::Glui_Color(50,50,50,100));
    GLUI::Gl_Print_Rectangle(WndW - 150, WndH -  70,140,30,GLUI::Glui_Color(50,50,50,100));
    GLUI::Gl_Print_Rectangle(WndW - 150, WndH - 100,140,30,GLUI::Glui_Color(50,50,50,100));
    GLUI::Gl_Print_Rectangle(WndW - 150, WndH - 130,140,30,GLUI::Glui_Color(50,50,50,100));
    text.glText(WndW - 140, WndH - 30,"Score : " + to_string(game.Score),TextColor);
    text.glText(WndW - 140, WndH - 60,"Lines : " + to_string(game.Lines),TextColor);
    text.glText(WndW - 140, WndH - 90,"Level : " + to_string(game.Level),TextColor);
    text.glText(WndW - 140, WndH - 120,"High : " + to_string(game.HighScore),TextColor);
    //message window
    static bool g_over = false;
    if(pause || game.GameOver)
    {
        GLUI::Gl_Print_Roundrect((WndW - 150 - 200)/2, (WndH-140)/2,200,140,50,GLUI::Glui_Color(150,200,0,100),GLUI::Glui_Color(20,20,20,150));
        if(game.GameOver)
        {
            if(!g_over){
                g_over = true;
                gameSound.Pause();
                gameOverSound.Play();
            }
            text.glText((WndW - 150 - 100)/2-3, (WndH-15)/2,"GAME OVER",TextColor);
            GLUI::Glui_Color col = TextColor.getNegative();
            col.setAlpha(80);
            GLUI::Gl_Print_Roundrect((WndW - 150 - 100)/2 -25, (WndH - 15)/2 - 26,150,20,10,col,col);
            text.glText((WndW - 150 - 100)/2 - 15, (WndH-15)/2 - 20,"Press Enter for a new game",TextColor,GLUT_BITMAP_HELVETICA_10);
        } else {
            text.glText((WndW - 150 - 60)/2, (WndH-15)/2,"PAUSE",TextColor);
        }
    }else {g_over = false;}

    muzOffButton.Draw();
    soundOffButton.Draw();

    glutSwapBuffers();
}

void readConfig()
{
    //add window heght
    config.addNewOption("Size","heigh",WndH);
    //add all colors to the config
    config.addNewOption("Color","background",BackgroundColor.getUInt());
    config.addNewOption("Color","text",TextColor.getUInt());
    config.addNewOption("Color","game",game.gatBckgColor().getUInt());
    //add resource files path to the config
    config.addNewOption("Path","blocksColor",blocksColorPath);
    config.addNewOption("Path","blocks",blocksPath);
    config.addNewOption("Path","gameSound",gameSoundPath);
    config.addNewOption("Path","pauseSound",pauseSoundPath);
    config.addNewOption("Path","rotateSound",rotateSoundPath);
    config.addNewOption("Path","gameOverSound",gameOverSoundPath);
    //add game blocks count to the config
    config.addNewOption("Value","gameBlockW",game.getW());
    config.addNewOption("Value","gameBlockH",game.getH());
    config.addNewOption("Value","muzOn",1);
    config.addNewOption("Value","soundOn",1);
    //add sounds volune
    config.addNewOption("Volume","muz",40);
    config.addNewOption("Volume","sounds",100);

    //read window heigh
    WndH = config.getOptionToInt("Size","heigh");
    //read colors from config
    BackgroundColor.setUInt(config.getOptionToUInt("Color","background"));
    TextColor.setUInt(config.getOptionToUInt("Color","text"));
    game.setBckgColor(GLUI::Glui_Color::UIntToColor(config.getOptionToUInt("Color","game")));
    window.setBckgColor(game.gatBckgColor());
    //read paths from config
    blocksColorPath = config.getOptionToString("Path","blocksColor");
    blocksPath = config.getOptionToString("Path","blocks");
    gameSoundPath = config.getOptionToString("Path","gameSound");
    pauseSoundPath = config.getOptionToString("Path","pauseSound");
    rotateSoundPath = config.getOptionToString("Path","rotateSound");
    gameOverSoundPath = config.getOptionToString("Path","gameOverSound");
    //read game blocks count from config
    int w = config.getOptionToInt("Value","gameBlockW");
    int h = config.getOptionToInt("Value","gameBlockH");
    gameSound.setActive(config.getOptionToInt("Value","muzOn"));
    soundsOn(config.getOptionToInt("Value","soundOn"));
    //read sounds volume
    gameSound.setVolume(config.getOptionToInt("Volume","muz"));
    int vol = config.getOptionToInt("Volume","sounds");
    //set volumes
    pauseSound.setVolume(vol);
    rotateSound.setVolume(vol);

    // calculate window size
    if(h == 0)
        return;
    int l = (WndH-20) / h;
    WndW = w*l+20+150;
    game.setBlocksCount(w,h);
}

void init()
{
    srand(time(NULL));
    //Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    game.LoadBlocksFromFile(blocksPath);
    game.LoadBlocksColorsFromFile(blocksColorPath);
    game.setSaveingFileName("Save");
    game.InitFrame(10,10,WndW-20-150,WndH-20);
    window.LoadBlocksFromFile(blocksPath);
    window.LoadBlocksColorsFromFile(blocksColorPath);
    window.InitFrame(WndW - 150, WndH - 300,140,140);
    window.NextBlockID = game.NextBlockID;
    window.NextBlockColorID = game.NextBlockColorID;
    window.NewGame();
    window.Next();
    //Sound init
    gameSound.Open(gameSoundPath);
    gameSound.Play();
    pauseSound.Open(pauseSoundPath);
    pauseSound.Loop = false;
    rotateSound.Open(rotateSoundPath);
    rotateSound.Loop = false;
    gameOverSound.Open(gameOverSoundPath);
    gameOverSound.Loop = false;
    //buttons init
    muzOffButton.X = WndW - 150;
    muzOffButton.Y = WndH - 340;
    muzOffButton.W = 30;
    muzOffButton.H = 30;
    muzOffButton.Color = GLUI::Glui_Color(50,50,50,100);
    muzOffButton.Checked = &gameSound;
    
    soundOffButton.X = WndW - 110;
    soundOffButton.Y = WndH - 340;
    soundOffButton.W = 30;
    soundOffButton.H = 30;
    soundOffButton.Color = GLUI::Glui_Color(50,50,50,100);
    soundOffButton.Checked = &pauseSound;

    TimerDisplay();
    Timer();
}
void Keys(BYTE key,int ax,int ay)
{
    switch (key)
    {
        case 27: exit(0);
            break;
        case 'p':
        case 'P':
            pause = !pause;
            if(pause)
            {
                gameSound.Pause();
                pauseSound.Play();
            }else{
                gameSound.Play();
                pauseSound.Play();
            }
            break;
        case 13:
            if(game.GameOver)
            {
                gameSound.Stop();
                gameSound.Play();
                game.NewGame();
                pause = false;
            }
            break;
        default:
            break;
    }

    if(!pause)
        game.KeyboardFunc(key,ax,WndH-ay);
}

void Keys(int key,int ax,int ay)
{
    if(!pause)
    {
        if(key == GLUT_KEY_UP)
            rotateSound.Play();
        game.SpecialFunc(key,ax,WndH - ay);
    }
}

void PassiveMotionFunc(int ax,int ay)
{
    muzOffButton.PassiveMotionFunc(ax,WndH - ay);
    soundOffButton.PassiveMotionFunc(ax,WndH - ay);
}
void MouseFunc(int button,int state,int ax,int ay)
{
    if(muzOffButton.MouseFunc(button, state, ax, WndH - ay))
    {
        //muz off or on
        gameSound.setActive(!gameSound.getActive());
        config.updateOption("Value","muzOn",gameSound.getActive());
    }
    
    if(soundOffButton.MouseFunc(button, state, ax, WndH - ay))
    {
        //sound off or on
        soundsOn(!pauseSound.getActive());
        config.updateOption("Value","soundOn",pauseSound.getActive());
    }
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
    gameSound.Update();
}

void TimerDisplay(int t)
{
    glutPostRedisplay();
    glutTimerFunc(200,TimerDisplay,t);
}

int main(int argc,char** argv)
{
    readConfig();
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
    //mouse fonc
    glutPassiveMotionFunc(PassiveMotionFunc);
    glutMouseFunc(MouseFunc);

    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}

void soundsOn(bool state)
{
    pauseSound.setActive(state);
    rotateSound.setActive(state);
    gameOverSound.setActive(state);
}