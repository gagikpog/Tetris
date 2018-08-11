#include "Tetris.h"

Game::Game(int w,int h)
{
    W = w;
    H = h;
    Matrix.insert(Matrix.begin(),H, std::vector<bool>());
    for(int i = 0; i < H;i++){
        Matrix[i].insert(Matrix[i].begin(), W, false);
    }
    backgrColor = new GLUI::Glui_Color(20,20,20);
}

void Game::InitFrame(int x, int y, int w, int h)
{
    PosX = x;
    PosY = y;
    SizeW = w;
    SizeH = h;
}

void Game::Print()
{
    backgrColor->Init();
    glBegin(GL_QUAD_STRIP);
        glVertex2f(PosX        , PosY);
        glVertex2f(PosX        , PosY + SizeH);
        glVertex2f(PosX + SizeW, PosY);      
        glVertex2f(PosX + SizeW, PosY + SizeH);  
    glEnd();
}

void Game::Next()
{

}