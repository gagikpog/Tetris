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
	
	GLUI::Glui_Color colN = col.getNegative();
	colN.setAlpha(255);
	GLUI::Gl_Print_Rectangle(X + W*0.12f,Y+H*0.35f,W*0.3f,H*0.3f,colN,colN);
	GLUI::Gl_Print_Polygon(X+W*0.08f,Y+H*0.2f,W*0.3f,3,colN,colN,180);

	glBegin(GL_LINES);
	glVertex2f(X + W*0.6f, Y + H*0.4f);
	glVertex2f(X + W*0.6f, Y + H*0.6f);


	glVertex2f(X + W*0.65f, Y + H*0.3f);
	glVertex2f(X + W*0.7f, Y + H*0.5f);
	glVertex2f(X + W*0.7f, Y + H*0.5f);
	glVertex2f(X + W*0.65f, Y + H*0.7f);

	glVertex2f(X + W*0.7f, Y + H*0.2f);
	glVertex2f(X + W*0.75f, Y + H*0.3f);
	glVertex2f(X + W*0.75f, Y + H*0.3f);
	glVertex2f(X + W*0.8f, Y + H*0.5f);

	glVertex2f(X + W*0.8f, Y + H*0.5f);
	glVertex2f(X + W*0.75f, Y + H*0.7f);
	glVertex2f(X + W*0.75f, Y + H*0.7f);
	glVertex2f(X + W*0.7f, Y + H*0.8f);

	glEnd();

	if(Checked)
	{
		if(!(*Checked).getActive())
		{
			col.getNegative().Init();
			glLineWidth(4);
			glBegin(GL_LINES);
			glVertex2f(X + W * 0.2f, Y + H * 0.2f);
			glVertex2f(X + W * 0.8f, Y + H * 0.9f);
			
			glVertex2f(X + W * 0.8f, Y + H * 0.2f);
			glVertex2f(X + W * 0.2f, Y + H * 0.8f);
			glEnd();
			glLineWidth(1);
		}
	}
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