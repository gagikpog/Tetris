#include <vector>
#include <string>
#include <fstream>
#include "lib/GluiColor.h"
#include "lib/Glui_UF.h"

#ifndef TETRIS_H
#define TETRIS_H


enum RotateType{
  R_Full,R_semi,R_none
};

class Block
{
  private:
    std::vector<std::vector<unsigned int>>* Matrix = NULL;
    std::vector<std::vector<bool>> mBlock;
    int X = 0,Y = 0;
    RotateType rType = R_Full;
  public:
    Block(std::vector<std::vector<unsigned int>>* matrix);
    ~Block(){}
    void Next();
    void Rotate();
    void setBlock(std::string str);
    void Print();
};


class Game
{
  private:
    int W,H;
    std::vector<std::vector<unsigned int>> Matrix;
    int Score;
    float PosX = 0,PosY = 0;
    float SizeW = 100,SizeH = 100;
    GLUI::Glui_Color* backgrColor;
    std::vector<std::string> blocksMap;
    void LoadBlocks(std::string filename);
  public:
    Game(int w,int h);
    ~Game();
    void InitFrame(float positionX, float positionY, float width, float height);
    void Print();
    void Next();
};

#endif