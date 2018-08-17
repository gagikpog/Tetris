#include "GluiColor.h"
#include <sstream>
#include <string>
#include <stdexcept>

#ifndef GLUI_UF
#define GLUI_UF
    namespace GLUI
    {
        float rotate_x(float x, float y, float alpha);
        float rotate_y(float x, float y, float alpha);
        //прямоугольник с закругленными краями контур
        void Gl_Print_Roundrect_Contour(float X, float Y, float W, float H, float R, Glui_Color Outline_color = Black, float _angle = 0, float line_width = 1);
        //прямоугольник с закругленными краями
        void Gl_Print_Roundrect(float X, float Y, float W, float H, float R, Glui_Color Color, Glui_Color Outline_color = Black, float _angle = 0, bool glossy = 1, float line_width = 1);
        //окружность контур
        void Gl_Print_Circle_Contour(float X, float Y, float R, Glui_Color Outline_color = Black, float line_width = 1);
        //окружность
        void Gl_Print_Circle(float X, float Y, float R, Glui_Color Color, Glui_Color Outline_color = Black, float line_width = 1);

        void Gl_Print_Rectangle_Contour(float X, float Y, float W, float H, Glui_Color Outline_color = Black, float _angle = 0, float line_width = 1);
        //прямоугольник
        void Gl_Print_Rectangle(float X, float Y, float W, float H, Glui_Color Color, Glui_Color Outline_color = Black, float _angle = 0, bool glossy = 1, float line_width = 1);
        //круг контур
        void Gl_Print_Circle_Contour(float X, float Y, float r, float R, Glui_Color Color, Glui_Color Outline_color = Black);
        //многоугольник
        void Gl_Print_Polygon_Contour(float X, float Y, float R, int Sides, Glui_Color Outline_color = Black, float initial_angle = 0, float line_width = 1);
        //многоугольник
        void Gl_Print_Polygon(float X, float Y, float R, int Sides, Glui_Color Color, Glui_Color Outline_color = Black, float initial_angle = 0, float line_width = 1);
    } // namespace GLUI

    namespace std{
        template<typename T>    
        std::string to_string(T arg)
        {
            std::stringstream res;
            res<<arg;
            return res.str();
        }
    }
#endif