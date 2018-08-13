#include "Tetris.h"

//--------Block-------------------
Block::Block(std::vector<std::vector<unsigned int>>* matrix)
{
    Matrix = matrix;
    mBlock.insert(mBlock.begin(),5,std::vector<bool>(5,0));
    Color = new GLUI::Glui_Color(GLUI::Glui_Color::UIntToColor(rand()+100));
}
Block::~Block()
{
    delete Color;
}
void Block::Next()
{
    if(Y < Matrix->size()-1)
        Y++;
}
void Block::Left()
{
    X--;
}
void Block::Right()
{
    X++;
}
void Block::Rotate()
{
    //R_Full,R_semi,R_none
    switch (rType)
    {
        case R_Full:
            Rotate90();
            break;
        case R_semi:
            if(rutateIndex)
                Rotate90();
            else Rotate270();
            rutateIndex = !rutateIndex;
        default:
            break;
    }
}
void Block::setBlock(std::string str)
{
    rType = (RotateType)(str[0] - '0');
    Y = (str[1] - '0');
    if(Matrix)
        X = (*Matrix)[0].size()/2;
    for(int i = 0; i < 25; i++)
    {
        mBlock[i/5][i%5] = str[i + 2] == '+';
    } 
}
void Block::Print(float x,float y,float w,float h)
{
    if(!Matrix)
        return;
    for(int i = -2; i < 3; i++)
    {
        if(Y + i < 0 || Y + i >= Matrix->size())
            continue;
        for(int j = -2; j < 3; j++)
        {
            if(X + j < 0 || X + j >= (*Matrix)[0].size())
                continue;
            if(mBlock[i+2][j+2])
                GLUI::Gl_Print_Rectangle(x+(X + j)*w,y+(Matrix->size()- Y - i - 1)*h,w,h,*Color,GLUI::Black,0,true,1);
        }        
    }   
}

void Block::Rotate90()
{
    bool tmp;
    int n = 5;
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = i; j < n - 1 - i; j++)
        {
            tmp = mBlock[i][j];
            mBlock[i][j] = mBlock[n - j - 1][i];
            mBlock[n - j - 1][i] = mBlock[n - i - 1][n - j - 1];
            mBlock[n - i - 1][n - j - 1] = mBlock[j][n - i - 1];
            mBlock[j][n - i - 1] = tmp;
        }
    }
}
void Block::Rotate270()
{
    bool tmp;
    int n = 5;
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = i; j < n - 1 - i; j++)
        {
            tmp = mBlock[i][j];
            mBlock[i][j] = mBlock[j][n - 1 - i];
            mBlock[j][n - 1 - i] = mBlock[n - 1 - i][n - 1 - j];
            mBlock[n - 1 - i][n - 1 - j] = mBlock[n - 1 - j][i];
            mBlock[n - 1 - j][i] = tmp;
        }
    }
}

//--------Game--------------------
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
    GLUI::Gl_Print_Rectangle(PosX,PosY,SizeW,SizeH,*backgrColor,GLUI::Red,0,true,1);

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
        block->Next();
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