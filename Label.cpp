#include "Label.h"

Label::Label()
{
	
}

Label::~Label()
{
}
void Label::Draw()
{
	GLUI::Glui_Color col = Color;
	if(passiveMouse)
		col = col.getNegative();
	GLUI::Gl_Print_Roundrect(X,Y,W,H,10,col,col.getNegative());
}

int Label::MouseFunc(int button, int state, int ax, int ay)
{
	if(button == 0 && state == 0)
	{
		if(ax > X && ax < X + W && ay > Y && ay < Y + H)
		{
			return 1;
		}
	}
	return 0;
}

int Label::PassiveMotionFunc(int ax, int ay)
{

	if (ax > X && ax < X + W && ay > Y && ay < Y + H)
	{
		passiveMouse = true;
		return 1;
	}else passiveMouse = false;
	return 0;
}