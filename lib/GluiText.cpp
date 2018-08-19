#include "GluiText.h"

namespace GLUI
{
	Glui_Text::Glui_Text()
	{
		size_text = 12;
		W = H = 0;
	}
	Glui_Text::~Glui_Text()
	{
	}
	void Glui_Text::setFontSize(int _size)
	{
		size_text = _size;
		H = 0;
	}
	void Glui_Text::setHeightChar(int _h)
	{
		H = _h;
		size_text = _h;
	}
	void Glui_Text::setWidthChar(int _w)
	{
		W = _w;
	}
	void Glui_Text::glText(float x, float y, const std::string txt, Glui_Color col,void* font)
	{
		col.Init();
		if (H > 0)
			y += H * 0.1;

		glRasterPos2f(x, y);
		int len = txt.length();
		for (int i = 0; i < len; i++)
		{
			glutBitmapCharacter(font, txt[i]);
		}
	}
	float Glui_Text::getTextLength(std::string txt)
	{
		return 0;
	}
	void Glui_Text::setFont(std::string font_name)
	{
		Font = font_name;
	}
} // namespace GLUI