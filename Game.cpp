#include "Game.h"

Game::Game(int w,int h)
{
    W = w;
    H = h;
    LoadBlocks("blocksMap.map");
    Matrix.insert(Matrix.begin(),H, std::vector<unsigned int>(W,0));
    block = new Block(&Matrix);
    block->setBlock(blocksMap[6]);
    backgrColor = new GLUI::Glui_Color(20,20,20);
}
Game::~Game()
{
    delete backgrColor;
}

void Game::LoadBlocks(std::string filename)
{
   std::ifstream fin(filename);
   if(fin.is_open())
   {
       std::string str;
       while(!fin.eof())
       {
            std::getline(fin,str);
            blocksMap.push_back(str);
       }
   }else throw std::runtime_error("Could not open file");
}

void Game::InitFrame(float x, float y, float w, float h)
{
    PosX = x;
    PosY = y;
    SizeW = w;
    SizeH = h;
}

void Game::Print()
{
    //  background
    GLUI::Gl_Print_Rectangle(PosX,PosY,SizeW,SizeH,*backgrColor,GLUI::Yellow,0,true,1);

    //  matrix
    float w = SizeW / W;
    float h = SizeH / H;
    for(int i = 0;i < H;i++)
    {
        for(int j = 0;j < W;j++)
        {
            if(Matrix[i][j] != 0)
                GLUI::Gl_Print_Rectangle(PosX+j*w,PosY+(H-i-1)*h,w,h,GLUI::Glui_Color::UIntToColor(Matrix[i][j]),GLUI::Yellow);
        }
    }
    block->Print(PosX,PosY,w,h);
}

void Game::Next()
{
    if(block)
    {
        if(!block->Next())
        {
            delete block;
            block = new Block(&Matrix);
            block->setBlock(blocksMap[rand()%blocksMap.size()]);
        }        
    }
}

void Game::KeyboardFunc(BYTE key,int ax,int ay)
{
    switch(key)
    {
        case 'r':
        break;
    }
}
void Game::SpecialFunc(int key,int ax,int ay)
{
    if(!block)
        return;
    switch(key)
    {
        case GLUT_KEY_LEFT:
            block->Left();
            break;
        case GLUT_KEY_RIGHT:
            block->Right();
            break;
        case GLUT_KEY_DOWN:
            block->Next();
            break;
        case GLUT_KEY_UP:
            block->Rotate();
            break;
    }
    glutPostRedisplay();
}

void Game::setBckgColor(const GLUI::Glui_Color& color)
{
    backgrColor = new GLUI::Glui_Color(color);
}