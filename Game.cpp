#include "Game.h"

Game::Game(int w,int h)
{
    W = w;
    H = h;
    Matrix.insert(Matrix.begin(),H, std::vector<unsigned int>(W,0));
    block = new Block(&Matrix);
    backgrColor = new GLUI::Glui_Color(22,215,255);
    blocksColor.push_back(GLUI::Glui_Color::ColorToUInt(GLUI::Green));
    ReadHighScore("HighScore");
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
            if(Matrix[i][j] != 0){
                GLUI::Glui_Color col(GLUI::Glui_Color::UIntToColor(Matrix[i][j]));
                GLUI::Gl_Print_Rectangle(PosX+j*w,PosY+(H-i-1)*h,w,h,col,col.getNegative());
            }
        }
    }
    //animation
    if(Pause)
    {
        GLUI::Glui_Color col = *backgrColor;
        col.setAlpha(180);
        for(int i = 0; i < erase.size(); i++)
        {
            GLUI::Gl_Print_Rectangle(PosX,PosY +( H - erase[i] -1)*h,animation*SizeW / 25,h,col,col);
            GLUI::Gl_Print_Rectangle(PosX + SizeW,PosY +( H - erase[i] -1)*h,-animation*SizeW / 25,h,col,col);
        }        
    }
    //  blocks
    block->Print(PosX,PosY,w,h);
}

bool Game::Next()
{
    if(Pause)
    {
        AnimationStep();
        return false;
    }

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
    if(!block || Pause)
        return;
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
    if(!block || Pause)
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

const GLUI::Glui_Color& Game::gatBckgColor() const
{
    return *backgrColor;
}

void Game::DeleteExtraLines()
{
    if(Pause)
    {
        return;
    }
    erase.clear();
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
            Pause = true;
        }        
    }
    
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
    if(Score > HighScore)
    {
        HighScore = Score;
        SaveHighScore("HighScore");
    }
    Lines += erase.size();
    Level = Lines / 10 + 1;
    Speed = 550 - Level*50;
    if(Pause)
        Speed = 20;

}

void Game::AnimationStep()
{
    if(animation >= 25)
    {
        animation  = 0;
        Pause = false;
        Speed = 550 - Level*50;

        for(int i = erase.size() - 1; i >= 0; i--)
        {
            Matrix.erase(Matrix.begin()+erase[i]);
        }    
        Matrix.insert(Matrix.begin(),erase.size(),std::vector<unsigned int>(Matrix[0].size(),0));
    }
    animation++;
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

void Game::SaveHighScore(std::string filname)
{
    std::ofstream fout(filname);
    if(fout.is_open())
    {
        BYTE str[] = "record____";
        str[6] = (BYTE) (HighScore >>24);
        str[7] = (BYTE) ((HighScore >> 16) & 255);
        str[8] = (BYTE) ((HighScore >> 8) & 255);
        str[9] = (BYTE) (HighScore & 255);
        unsigned int crc = getCRC(str,10);
        fout.write((char*)&str,10);
        fout.write((char*)&crc,sizeof(int));
    }else{
        throw std::runtime_error("Can't create or open file for saving high score");
    }

}

void Game::ReadHighScore(std::string filname)
{
    std::ifstream fin(filname);
    if(fin.is_open())
    {
        BYTE str[] = "record____";
        unsigned int crc;
        fin.read((char*)str,10);
        fin.read((char*)&crc,sizeof(int));
                
        if(getCRC(str,10) == crc)
        {
            HighScore  = str[6]; HighScore <<=8;
            HighScore |= str[7]; HighScore <<=8;
            HighScore |= str[8]; HighScore <<=8;
            HighScore |= str[9];            
        }else {std::cout<<"HighScore file was damaged\n";}

    }else{
        throw std::runtime_error("Can't create or open file for saving high score");
    }

}