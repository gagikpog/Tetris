#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <random>
#include "lib/Glui_UF.h"
#ifndef BLOCK_H
#define BLOCK_H

enum RotateType{
  R_Full,R_semi,R_none
};

class Block
{
private:
  std::vector<std::vector<unsigned int>> *Matrix = NULL;
  std::vector<std::vector<bool>> mBlock;
  int X = 0, Y = 0;
  RotateType rType = R_Full;
  GLUI::Glui_Color *Color;
  void Rotate90(bool Adjustment = true);
  void Rotate270(bool Adjustment = true);
  bool rutateIndex = 0;
  bool Dead = false;
  void Save();
  bool PositionAdjustment(BYTE deep = 3);
public:
  Block(std::vector<std::vector<unsigned int>> *matrix);
  ~Block();
  bool Next();
  void Left();
  void Right();
  void Rotate();
  void setBlock(std::string str);
  void Print(float feameX, float frameY, float frameW, float frameH);
};
#endif