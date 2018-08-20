#include <string>
#include "GluiColor.h"

#ifndef GLUITEXT_H
#define GLUITEXT_H

namespace GLUI
{
	class Glui_Text
	{
	public:
		Glui_Text();
		~Glui_Text();
		//установка размера шрифта
		void setFontSize(int _size);
		//установка размера шрифта
		void setHeightChar(int _h);
		//установка размера шрифта
		void setWidthChar(int _w);
		//печатает текст по заданным координатам
		void glText(float x, float y, const std::string& txt, Glui_Color col = Black,void* font = GLUT_BITMAP_HELVETICA_18);
		//
		float getTextLength(std::string txt);
		//устанавливает дескриптор контекста устройства
		void setFont(std::string font_name);

	private:
		float W, H;
		int size_text;
		GLuint arial;
		std::string Font = "Arial";
	};
} // namespace GLUI
#endif