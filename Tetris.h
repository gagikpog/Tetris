#include <iostream>
#include <GL/freeglut.h>
#include <vector>
#include "GluiColor.h"

#ifndef TETRIS_H
#define TETRIS_H


class Block
{
  private:
    
  public:
    Block(){}
    ~Block(){}
};


class Game
{
  private:
    int W,H;
    std::vector<std::vector<bool>> Matrix;
    int Score;
    int PosX = 0,PosY = 0;
    int SizeW = 100,SizeH = 100;
    GLUI::Glui_Color* backgrColor;
  public:
    Game(int w,int h);
    ~Game(){}
    void InitFrame(int positionX, int positionY, int width, int height);
    void Print();
    void Next();
};

#endif