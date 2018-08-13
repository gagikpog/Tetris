#include "Block.h"

#ifndef GAME_H
#define GAME_H

class Game
{
private:
  int W, H;
  std::vector<std::vector<unsigned int>> Matrix;
  int Score;
  float PosX = 0, PosY = 0;
  float SizeW = 100, SizeH = 100;
  GLUI::Glui_Color *backgrColor;
  std::vector<std::string> blocksMap;
  void LoadBlocks(std::string filename);
  Block *block = NULL;

public:
  Game(int w, int h);
  ~Game();
  void InitFrame(float positionX, float positionY, float width, float height);
  void Print();
  void Next();
  void KeyboardFunc(BYTE key, int ax, int ay);
  void SpecialFunc(int key, int ax, int ay);
  void setBckgColor(const GLUI::Glui_Color& color);
  int Speed = 500;
};

#endif