#include "Glui_UF.h"

namespace GLUI
{

    float rotate_x(float x, float y, float alpha)
    {
       if (alpha == 0)
            return x;
        float l, a1;
        l = sqrtf(x*x + y*y);
        if (x || y)
            a1 = atan2f(y, x) * 180.0f / PI;
        else a1 = 0.0f;
        alpha += a1;

        x = cosf(alpha*PI / 180.0f)*l;
        return x;
    }
    float rotate_y(float x, float y, float alpha)
    {
        if (alpha == 0)
            return y;
        float l, a1;
        l = sqrtf(x*x + y*y);
        if (x || y)
            a1 = atan2f(y, x) * 180.0f / PI;
        else a1 = 0.0f;
        alpha += a1;

        y = sinf(alpha*PI / 180.0f)*l;
        return y;
    }
    
    void Gl_Print_Roundrect_Contour(float X, float Y, float W, float H, float R, Glui_Color Outline_color, float _angle,float line_width)
    {
        float fx, fy, RX, RY;
        float R1 = R;
        
        if (R < H / 2.0f && R < W / 2.0f)
        {
            R1 = R;
        }
        else
        {
            if (W > H)
                R1 = H / 2.0f;
            else R1 = W / 2.0f;
        }

        float siny(0), cosx(0);
        float fi;
        glLineWidth(line_width);
        glBegin(GL_LINE_LOOP);
        Outline_color.Init();

        RX = X + W - R1;
        RY = Y + H - R1;
        for (float i = 0; i <= PI / 2; i += 0.1f)
        {
            fx = RX + cos(i)*R1;
            fy = RY + sin(i)*R1;
            glVertex2f(rotate_x(fx - X, fy - Y, _angle) + X, rotate_y(fx - X, fy - Y, _angle) + Y);
        }

        RX = X + R1;
        RY = Y + H - R1;
        for (float i = PI / 2.0f; i <= PI; i += 0.1f)
        {
            fx = RX + cos(i)*R1;
            fy = RY + sin(i)*R1;
            glVertex2f(rotate_x(fx - X, fy - Y, _angle) + X, rotate_y(fx - X, fy - Y, _angle) + Y);
        }

        RX = X + R1;
        RY = Y + R1;
        for (float i = PI; i <= PI * 3 / 2; i += 0.1f)
        {
            fx = RX + cos(i)*R1;
            fy = RY + sin(i)*R1;
            glVertex2f(rotate_x(fx - X, fy - Y, _angle) + X, rotate_y(fx - X, fy - Y, _angle) + Y);
        }

        RX = X + W - R1;
        RY = Y + R1;
        for (float i = PI * 3 / 2; i <= PI * 2.0f; i += 0.1f)
        {
            fx = RX + cos(i)*R1;
            fy = RY + sin(i)*R1;
            glVertex2f(rotate_x(fx - X, fy - Y, _angle) + X, rotate_y(fx - X, fy - Y, _angle) + Y);
        }
        glEnd();
        glLineWidth(1);
    }
    
    void Gl_Print_Roundrect(float X, float Y, float W, float H, float R, Glui_Color Color, Glui_Color Outline_color, float _angle, bool glossy,float line_width)
    {
        float fx, fy, RX, RY;
        float R1 = R;

        if (R < H / 2.0f && R < W / 2.0f)
        {
            R1 = R;
        }
        else
        {
            if (W > H)
                R1 = H / 2.0f;
            else R1 = W / 2.0f;
        }

        float siny(0), cosx(0);
        float fi;
        glBegin(GL_POLYGON);
        Color.Init();

        RX = X + W - R1;
        RY = Y + H - R1;
        for (float i = 0; i <= PI / 2; i += 0.1f)
        {
            fx = RX + cos(i)*R1;
            fy = RY + sin(i)*R1;
            glVertex2f(rotate_x(fx - X,fy - Y, _angle) + X, rotate_y(fx - X,fy - Y,_angle) + Y);
        }

        RX = X + R1;
        RY = Y + H - R1;
        for (float i = PI / 2.0f; i <= PI; i += 0.1f)
        {
            fx = RX + cos(i)*R1;
            fy = RY + sin(i)*R1;
            glVertex2f(rotate_x(fx - X, fy - Y, _angle) + X, rotate_y(fx - X, fy - Y, _angle) + Y);
        }

        RX = X + R1;
        RY = Y + R1;
        for (float i = PI; i <= PI * 3 / 2; i += 0.1f)
        {
            fx = RX + cos(i)*R1;
            fy = RY + sin(i)*R1;
            glVertex2f(rotate_x(fx - X, fy - Y, _angle) + X, rotate_y(fx - X, fy - Y, _angle) + Y);
        }

        RX = X + W - R1;
        RY = Y + R1;
        for (float i = PI * 3 / 2; i <= PI * 2.0f; i += 0.1f)
        {
            fx = RX + cos(i)*R1;
            fy = RY + sin(i)*R1;
            glVertex2f(rotate_x(fx - X, fy - Y, _angle) + X, rotate_y(fx - X, fy - Y, _angle) + Y);
        }
        glEnd();
        Gl_Print_Roundrect_Contour(X, Y, W, H, R, Outline_color, _angle, line_width);
    }
    
    void Gl_Print_Circle_Contour(float X, float Y, float R, Glui_Color Outline_color, float line_width)
    {
        glLineWidth(line_width);
        glBegin(GL_LINE_LOOP);
        Outline_color.Init();
        for (float i = 0; i < 2 * PI; i += 0.1f)
        {
            glVertex2f(cos(i)*R + R + X, sin(i)*R + R + Y);
        }
        glEnd();
        glLineWidth(1);
    }
    
    void Gl_Print_Circle(float X, float Y, float R, Glui_Color Color, Glui_Color Outline_color, float line_width)
    {
        glBegin(GL_POLYGON);
        Color.Init();
        for (float i = 0; i < 2 * PI; i += 0.1f)
        {
            glVertex2f(cos(i)*R + R + X, sin(i)*R + R + Y);
        }
        glEnd();
        Gl_Print_Circle_Contour(X, Y, R, Outline_color, line_width);
    }
    
    void Gl_Print_Rectangle_Contour(float X, float Y, float W, float H, Glui_Color Outline_color, float _angle, float line_width)
    {
        glLineWidth(line_width);
        glBegin(GL_LINE_LOOP);
        Outline_color.Init();
        glVertex2f(X, Y);
        glVertex2f(X + rotate_x(W, 0, _angle), Y + rotate_y(W, 0, _angle));
        glVertex2f(X + rotate_x(W, H, _angle), Y + rotate_y(W, H, _angle));
        glVertex2f(X + rotate_x(0, H, _angle), Y + rotate_y(0, H, _angle));
        glEnd();
        glLineWidth(1);
    }
    
    void Gl_Print_Rectangle(float X, float Y, float W, float H, Glui_Color Color, Glui_Color Outline_color, float _angle, bool glossy, float line_width)
    {
        Color.Init();
        glBegin(GL_POLYGON);
        if (glossy)
            Color.Init(0);
        glVertex2f(X, Y);
        if (glossy)
            Color.Init(0);
        glVertex2f(X + rotate_x(W, 0, _angle), Y + rotate_y(W, 0, _angle));
        if (glossy)
            Color.Init(0);
        glVertex2f(X + rotate_x(W, H, _angle), Y + rotate_y(W, H, _angle));
        if (glossy)
            Color.Init(0);
        glVertex2f(X + rotate_x(0, H, _angle), Y + rotate_y(0, H, _angle));
        glEnd();
        Gl_Print_Rectangle_Contour(X,Y,W,H,Outline_color,_angle,line_width);
    }
    
    void Gl_Print_Circle_Contour(float X, float Y, float r, float R, Glui_Color Color, Glui_Color Outline_color)
    {
        glBegin(GL_TRIANGLE_STRIP);
        Color.Init();
        for (float i = 0; i <= 2 * PI; i += 0.001f)
        {
            glVertex2f(X + R + cosf(i)*R, Y + R + sinf(i)*R);
            glVertex2f(X + R + cosf(i)*r, Y + R + sinf(i)*r);
        }
        glEnd();
        Outline_color.Init();
        glBegin(GL_LINE_LOOP);
        for (float i = 0; i <= 2 * PI; i += 0.001f)
            glVertex2f(X + R + cosf(i)*R, Y + R + sinf(i)*R);
        glEnd();

        glBegin(GL_LINE_LOOP);
        for (float i = 0; i <= 2 * PI; i += 0.001f)
            glVertex2f(X + R + cosf(i)*r, Y + R + sinf(i)*r);
        glEnd();
    }
    
    void Gl_Print_Polygon_Contour(float X, float Y, float R, int Sides, Glui_Color Outline_color , float initial_angle, float line_width)
    {
        glLineWidth(line_width);
        Outline_color.Init();
        glBegin(GL_LINE_LOOP);
        for (float i = initial_angle * PI / 180; i < PI * 2 + initial_angle * PI / 180; i += PI * 2 / Sides)
            glVertex2f(X + R + cosf(i)*R, Y + R + sinf(i)*R);
        glEnd();
        glLineWidth(1);
    }
    
    void Gl_Print_Polygon(float X, float Y, float R, int Sides, Glui_Color Color, Glui_Color Outline_color , float initial_angle,float line_width)
    {
        Color.Init();
        glBegin(GL_POLYGON);
        for (float i = initial_angle * PI / 180.0f; i < PI * 2.0f + initial_angle * PI / 180.0f; i += PI * 2.0f / Sides)
            glVertex2f(X + R + cosf(i)*R, Y + R + sinf(i)*R);
        glEnd();
        Gl_Print_Polygon_Contour(X, Y, R, Sides, Outline_color, initial_angle, line_width);
    }

    char *str_cpy(char *l, const char *r) {
        while (*r) *l++ = *r++;
        ++*l = '\0';
        return l;
    }
}