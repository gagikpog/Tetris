#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846f

#ifndef WIN32
#define sqrtf sqrt
#define BYTE unsigned char
#define HDC short
#define HWND short
#define atan2f atan2
#define sinf sin
#define cosf cos
#define OpenClipboard
#endif

#ifndef GLUICOLOR_H
#define GLUICOLOR_H

namespace GLUI
{
	//перечисление цветов
	enum Glui_Colornum {
		Black, White, Red, Green, Blue, Cyan, Magenta, Yellow, Water, Plastic, Glass, Diamond, Iron, Copper, Gold, Aluminum, Silver, Deepskyblue,
		Lightskyblue, Mistyrose, Burlywood, Violet, Whitesmoke, Lime, Tan, Lightgray, Lightsteelblue, Yellowgreen, Orange, Coral, Fuchsia, Dodgerblue,
		Plum, Limegreen, Olive, Darkmagenta, Gray, Dimgray, Brown, Darkslategray, Firebrick, Sienna, Maroon, Darkblue, Navy, Other
	};

	//Глют цвета
	class Glui_Color
	{
	public:
		Glui_Color(BYTE red, BYTE green, BYTE blue, BYTE alpha = 255);
		Glui_Color(const Glui_Colornum& _color = Black);
		Glui_Color(const Glui_Color& _color);
		Glui_Color();
		~Glui_Color() {}
		//установка цвета
		Glui_Color& setColor(const Glui_Colornum& _color);
		Glui_Color& setColor(const Glui_Color& _color);
		//установка цвета
		Glui_Color& setColor(BYTE _red, BYTE _green, BYTE _blue, BYTE _alpha = 255);
		//установка прозрачности
		Glui_Color& setAlpha(const BYTE& _alpha);
		//определяет цвет отрисовки
		void Init(short bright = 0, BYTE _alpha = 0)const;
		//Возвращает цвета в uint
		unsigned int getUInt()const;
		//переобразует uint в цвета RGBA
		Glui_Color& setUInt(unsigned int count);
		//возвращает цвет в негативе
		Glui_Color getNegative()const;
		//не меняет значение
		Glui_Color operator+(int _c)const;
		//не меняет значение
		Glui_Color operator-(int _c)const;
		bool operator==(const Glui_Colornum& _col)const;
		bool operator==(const Glui_Color& _col)const;
		Glui_Color operator+(const Glui_Color& operator2)const;
		Glui_Color operator-(const Glui_Color& operator2)const;
		//static
		static unsigned int ColorToUInt(Glui_Color color);
		static Glui_Color UIntToColor(unsigned int intValue);
//		friend class Glui_ColDialog;
	private:
	protected:
		Glui_Color bildColor(Glui_Colornum _Color)const;
		Glui_Colornum  color;
		BYTE R, G, B, A;
	};

}
#endif