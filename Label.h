#include "lib/GluiColor.h"
#include "lib/Glui_UF.h"
#include "Sound.h"

#ifndef LABEL_H
#define LABEL_H

class Label
{
private:
	bool passiveMouse = false;
public:
	Label();
	~Label();
	int X = 0,Y = 0,W = 10,H = 10;
	GLUI::Glui_Color Color = GLUI::Black;
	void Draw();
	int MouseFunc(int button, int state, int ax, int ay);
	int PassiveMotionFunc(int ax, int ay);
	Sound *Checked = NULL;
};

#endif