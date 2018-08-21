#include "Block.h"
#include "lib/CRC_code.h"

#ifndef GAME_H
#define GAME_H

class Game
{
private:
  int W, H;
  std::vector<std::vector<unsigned int>> Matrix;
  float PosX = 0, PosY = 0;
  float SizeW = 100, SizeH = 100;
  GLUI::Glui_Color *backgrColor;
  std::vector<std::string> blocksMap;
  std::vector<unsigned int> blocksColor;
  std::vector<BYTE> erase;
  Block *block = NULL;
  bool Pause = false;
  int animation = 0;
  void DeleteExtraLines();
  void NewBlock();
  void AnimationStep();
  void OpenGameDump(std::string filename);
  void SaveGameDump(std::string filename);
  std::string saveFilename;
public:
  Game(int w, int h);
  ~Game();
  void InitFrame(float positionX, float positionY, float width, float height);
  void Print();
  bool Next();
  void KeyboardFunc(BYTE key, int ax, int ay);
  void SpecialFunc(int key, int ax, int ay);
  void setBckgColor(const GLUI::Glui_Color& color);
  const GLUI::Glui_Color& gatBckgColor() const;
  void LoadBlocksFromFile(std::string filename);
  void LoadBlocksColorsFromFile(std::string filename);
  void setSaveingFileName(std::string filename);
  void NewGame();
  int getW(){return W;}
  int getH(){return H;}
  void setBlocksCount(int w,int h);
  bool GameOver = false;
  int Speed = 500;
  int Level = 1;
  int Lines = 0;
  int Score = 0;
  int NextBlockID = 0;
  int HighScore = 0;
  int NextBlockColorID = 0;
};

#endif