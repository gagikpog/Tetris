#include "Game.h"

Game::Game(int w,int h)
{
    W = w;
    H = h;
    Matrix.insert(Matrix.begin(),H, std::vector<unsigned int>(W,0));
    block = new Block(&Matrix);
    backgrColor = new GLUI::Glui_Color(22,215,255);
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
    }else{
        std::cout<<"Could not open file "<<filename<<std::endl;
    }
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
    bool res = true;
    if(GameOver)
        return res;
    if(Pause)
    {
        AnimationStep();
        return res;
    }

    if(block)
    {
        res = block->Next();
        if(!res)
        {
            NewBlock();
            SaveGameDump(saveFilename);
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
        GameOver = true;
        Pause = true;
        return;
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
    Pause = false;
    GameOver = false;
    NewBlock();
    Speed = 500;
    Level = 1;
    Lines = 0;
    Score = 0;
    SaveGameDump(saveFilename);
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

void Game::SaveGameDump(std::string filename)
{
    if(Matrix.empty() || filename == "")
        return;
    /* Matrix save to file;
     * Matrix == vector<vector<int>
     * 1) Matrix to Uint[];
     * 2) Add an score, lines and a high score to the arr
     * 3) Uint[] to BYTE[]
     * 4) Get CRC code of BYTE[]
     * 5) Write BYTE[] and CRC code to the file 
     */
    int _size = 1/*<-see next line*/ + Matrix.size()*Matrix[0].size() + 3; //Last 3 int elements is score, lines and high score
    // In the first element of the array will be written the size of the matrix
    unsigned int* arr = new unsigned int[_size];
    // 1)
    arr[0] = 0;
    for(int i = 0; i < Matrix.size(); i++)
    {
        for(int j = 0; j < Matrix[i].size(); j++)
        {
            arr[ i*Matrix[i].size() + j + 1 ] = Matrix[i][j];
        }
    }
    // 2)
    arr[_size - 1] = HighScore;
    arr[_size - 2] = Lines;
    arr[_size - 3] = Score;
    // 3) // bArr size == _size*4
    BYTE * bArr = (BYTE*) arr;
    bArr[0] = Matrix.size();
    bArr[1] = Matrix[0].size();
    // 4)
    unsigned int crc = getCRC(bArr,_size*4);
    // 5)
    std::ofstream fout(filename);
    if(!fout.is_open())
    {
        throw std::runtime_error("Can't save game");
    }

    fout.write((char*)bArr,_size * 4);
    fout.write((char*)&crc,sizeof(int));
    fout.close();
    delete []arr;
}


void Game::OpenGameDump(std::string filename)
{
    if(filename == "")
        return;
    /* Read Matrix from file;
     * 1) Get Matrix size
     * 2) Calcole Uint array size
     * 3) Create Uint array
     * 4) Get BYTE pinter for Uint array
     * 5) Copy all file from BYTE array
     * 6) CRC code checked
     * 7) Get score, lines and high score from array
     * 8) Resize Matrix
     * 9) Filling Matrix
     */
    std::ifstream fin(filename);
    if(!fin.is_open())
    {
        std::cout<< "Can not open saved game\n";
        return;
    }
    // 1)
    unsigned int msize = 0;
    fin.read((char*)&msize,sizeof(int));
    int h = msize & 0x000000ff;
    int w = (msize >> 8)& 0x000000ff;
    // 2)
    int _size = w * h + 4;
    // 3)
    unsigned int* arr = new unsigned int[_size];
    // 4)
    BYTE* bArr = (BYTE*) arr;
    // 5)
    fin.read((char*)(bArr+4),(_size - 1)*4);
    //first element of array = msize
    arr[0] = msize;
    // 6)
    // read crc code from file
    unsigned int crc = 0;
    fin.read((char*)&crc,sizeof(int));
    if(crc != getCRC(bArr, _size*4))
    {
        std::cout<<"\n";
        return;
    }
    // 7
    HighScore = arr[_size - 1];
    Lines = arr[_size - 2];
    Score = arr[_size - 3];
    // 8)
    if(w != W || h != H)
    {
        NewGame();
        return;
    }
    // 9)
    
    for(int i = 0; i < h; i++)
    {        
        for(int j = 0; j < w; j++)
        {
            Matrix[i][j] = arr[1+i*w+j];
        }
    }   

    delete []arr;
}

void Game::setSaveingFileName(std::string filename)
{
    saveFilename = filename;
    OpenGameDump(saveFilename);
}

void Game::setBlocksCount(int w,int h)
{
    W = w;
    H = h;
    Matrix.clear();
    Matrix.insert(Matrix.begin(),H, std::vector<unsigned int>(W,0));
}