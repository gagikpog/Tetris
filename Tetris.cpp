#include "Tetris.h"


//--------Block-------------------
Block::Block(std::vector<std::vector<unsigned int>>* matrix)
{
    Matrix = matrix;
    mBlock.insert(mBlock.begin(),5,std::vector<bool>(5,0));
}
void Block::Next()
{

}
void Block::Rotate()
{

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
void Block::Print()
{
    
}
//--------Game--------------------
Game::Game(int w,int h)
{
    W = w;
    H = h;
    LoadBlocks("blocksMap.map");
    Matrix.insert(Matrix.begin(),H, std::vector<unsigned int>(W,0));
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
    ////////////////filling color
    for(int i = 0;i < H;i++)
    {
        for(int j = 0;j < W;j++)
        {
            Matrix[i][j] = (i+1)*185273088;
        }
    }
    //////////////
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
}

void Game::Next()
{

}