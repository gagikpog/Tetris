#include "Game.h"

Game::Game(int w,int h)
{
    W = w;
    H = h;
    Matrix.insert(Matrix.begin(),H, std::vector<unsigned int>(W,0));
    block = new Block(&Matrix);
    backgrColor = new GLUI::Glui_Color(20,20,20);
    blocksColor.push_back(GLUI::Glui_Color::ColorToUInt(GLUI::Green));
}
Game::~Game()
{
    delete backgrColor;
}

void Game::LoadBlocksFromFile(std::string filename)
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
    NextBlockID = rand()%blocksMap.size();
    block->setBlock(blocksMap[NextBlockID]);
   }else throw std::runtime_error("Could not open file 'blocksMap.map'");
}
void Game::LoadBlocksColorsFromFile(std::string filename)
{
    std::ifstream fin(filename);
    if (fin.is_open())
    {
        blocksColor.clear();
        unsigned int res;
        while (!fin.eof())
        {
            fin>>res;
            blocksColor.push_back(res);
        }
        NextBlockColorID = rand() % blocksColor.size();
        block->setBlockColor(GLUI::Glui_Color::UIntToColor(blocksColor[NextBlockColorID]));
    }
    else
        throw std::runtime_error("Could not open file 'blocksColor.txt'");
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
    //  blocks
    block->Print(PosX,PosY,w,h);
}

bool Game::Next()
{
    bool res = false;
    if(block)
    {
        res = block->Next();
        if(!res)
        {
           NewBlock();
        }        
    }
    return res;
}

void Game::KeyboardFunc(BYTE key,int ax,int ay)
{
    switch(key)
    {
        case 'r':
        case 'R':
            NewGame();       
        break;
        case ' ':
            while(block->Next());
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
    if(backgrColor)
        delete backgrColor;
    backgrColor = new GLUI::Glui_Color(color);
}


bool Game::DeleteExtraLines()
{
    std::vector<BYTE> erase;
    bool b = true;
    int delLineCount = 0;
    for(int i = 0; i < Matrix.size(); i++)
    {
        b = true;
        for(int j = 0; j < Matrix[0].size() && b; j++)
        {
            b = Matrix[i][j] != 0;
        }
        if(b){
            erase.push_back(i);
        }        
    }
    
    for(int i = erase.size() - 1; i >= 0; i--)
    {
        Matrix.erase(Matrix.begin()+erase[i]);
    }    
    Matrix.insert(Matrix.begin(),erase.size(),std::vector<unsigned int>(Matrix[0].size(),0));
   //game over
    bool gameOver = false;
    for (int i = 0; i < Matrix[0].size() && !gameOver; i++)
    {
        gameOver = Matrix[0][i] > 0;
    }
    if (gameOver)
    {
        NewGame();
    }
    // counting score and game status
    switch(erase.size())
    {
        case 1:
            Score += 40*Level;
            break;
        case 2:
            Score += 100*Level;
            break;
        case 3:
            Score += 300*Level;
            break;
        case 4:
            Score += 1200*Level;
            break;
    }
    Lines += erase.size();
    Level = Lines / 10 + 1;
    Speed = 550 - Level*50;

}

void Game::NewGame()
{
    for (int i = 0; i < Matrix.size(); i++)
    {
        for (int j = 0; j < Matrix[0].size(); j++)
        {
            Matrix[i][j] = 0;
        }
    }
    NewBlock();
    Speed = 500;
    Level = 1;
    Lines = 0;
    Score = 0;
}

void Game::NewBlock()
{
    delete block;
    block = new Block(&Matrix);
    block->setBlock(blocksMap[NextBlockID]);
    block->setBlockColor(GLUI::Glui_Color::UIntToColor(blocksColor[NextBlockColorID]));
    DeleteExtraLines();
    NextBlockID = rand() % blocksMap.size();
    NextBlockColorID = rand() % blocksColor.size();
}