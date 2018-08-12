#include "GluiColor.h"
namespace GLUI
{

Glui_Color::Glui_Color(BYTE red, BYTE green, BYTE blue, BYTE alpha)
{
    R = red;
    G = green;
    B = blue;
    A = alpha;
}
Glui_Color::Glui_Color(const Glui_Colornum &_color)
{
    this->setColor(bildColor(_color));
}
Glui_Color::Glui_Color(const Glui_Color &_color)
{
    R = _color.R;
    G = _color.G;
    B = _color.B;
    A = _color.A;
}
Glui_Color::Glui_Color()
{
    R = G = B = 0;
    A = 255;
}
Glui_Color &Glui_Color::setColor(const Glui_Colornum &_color)
{
    setColor(bildColor(_color));
    return *this;
}
Glui_Color &Glui_Color::setColor(const Glui_Color &_color)
{
    R = _color.R;
    G = _color.G;
    B = _color.B;
    A = _color.A;
    return *this;
}
Glui_Color &Glui_Color::setColor(BYTE _red, BYTE _green, BYTE _blue, BYTE _alpha)
{
    R = _red;
    G = _green;
    B = _blue;
    A = _alpha;
    return *this;
}
Glui_Color &Glui_Color::setAlpha(const BYTE &_alpha)
{
    A = _alpha;
    return *this;
}
void Glui_Color::Init(short bright, BYTE _alpha) const
{
    int _r, _g, _b;
    _r = R + bright;
    _g = G + bright;
    _b = B + bright;

    if (_r > 255)
        _r = 255;
    if (_r < 0)
        _r = 0;
    if (_g > 255)
        _g = 255;
    if (_g < 0)
        _g = 0;
    if (_b > 255)
        _b = 255;
    if (_b < 0)
        _b = 0;

    if (_alpha == 0)
        glColor4ub(_r, _g, _b, A);
    else
        glColor4ub(_r, _g, _b, _alpha);
}
Glui_Color Glui_Color::operator+(int _c) const
{
    short _r, _g, _b;
    _r = R + _c;
    _g = G + _c;
    _b = B + _c;
    if (_r > 255)
        _r = 255;
    if (_g > 255)
        _g = 255;
    if (_b > 255)
        _b = 255;

    if (_r < 0)
        _r = 0;
    if (_g < 0)
        _g = 0;
    if (_b < 0)
        _b = 0;
    return Glui_Color((BYTE)_r, (BYTE)_g, (BYTE)_b, A);
}
Glui_Color Glui_Color::operator-(int _c) const
{
    short _r, _g, _b;
    _r = R - _c;
    _g = G - _c;
    _b = B - _c;
    if (_r > 255)
        _r = 255;
    if (_g > 255)
        _g = 255;
    if (_b > 255)
        _b = 255;

    if (_r < 0)
        _r = 0;
    if (_g < 0)
        _g = 0;
    if (_b < 0)
        _b = 0;
    return Glui_Color((BYTE)_r, (BYTE)_g, (BYTE)_b, A);
}
bool Glui_Color::operator==(const Glui_Colornum &_col) const
{
    return this->operator==(bildColor(_col));
}
bool Glui_Color::operator==(const Glui_Color &_col) const
{
    return (_col.R == R && _col.G == G && _col.B == B && _col.A == A);
}
unsigned int Glui_Color::getUInt() const
{
    unsigned int t;
    t = R;
    t <<= 8;
    t += G;
    t <<= 8;
    t += B;
    t <<= 8;
    t += A;
    return t;
}
Glui_Color &Glui_Color::setUInt(unsigned int count)
{
    A = (count % 256);
    count >>= 8;
    B = (count % 256);
    count >>= 8;
    G = (count % 256);
    count >>= 8;
    R = (count % 256);
    return *this;
}
Glui_Color Glui_Color::getNegative() const
{
    return Glui_Color(255 - R, 255 - G, 255 - B, A);
}
Glui_Color Glui_Color::operator+(const Glui_Color &operator2) const
{
    short _r(R), _g(G), _b(B), _a(A);

    _r = (_r + operator2.R) / 2;
    _g = (_g + operator2.G) / 2;
    _b = (_b + operator2.B) / 2;
    _a = (_a + operator2.A) / 2;

    if (_r > 255)
        _r = 255;
    if (_r < 0)
        _r = 0;
    if (_g > 255)
        _g = 255;
    if (_g < 0)
        _g = 0;
    if (_b > 255)
        _b = 255;
    if (_b < 0)
        _b = 0;
    if (_a > 255)
        _a = 255;
    if (_a < 0)
        _a = 0;

    return Glui_Color(_r, _g, _b, _a);
}
Glui_Color Glui_Color::operator-(const Glui_Color &operator2) const
{
    short _r(R), _g(G), _b(B), _a(A);

    _r = 2 * _r - operator2.R;
    _g = 2 * _g - operator2.G;
    _b = 2 * _b - operator2.B;
    _a = 2 * _a - operator2.A;

    if (_r > 255)
        _r = 255;
    if (_r < 0)
        _r = 0;
    if (_g > 255)
        _g = 255;
    if (_g < 0)
        _g = 0;
    if (_b > 255)
        _b = 255;
    if (_b < 0)
        _b = 0;
    if (_a > 255)
        _a = 255;
    if (_a < 0)
        _a = 0;

    return Glui_Color(_r, _g, _b, _a);
}
Glui_Color Glui_Color::bildColor(Glui_Colornum _Color) const
{
    BYTE r, g, b;
    switch (_Color)
    {
    case Black:                 r = 0;          g = 000;        b = 000;        break;
    case White:                 r = 255;        g = 255;        b = 255;        break;
    case Red:                   r = 255;        g = 000;        b = 000;        break;
    case Green:                 r = 0;          g = 255;        b = 000;        break;
    case Blue:                  r = 0;          g = 000;        b = 255;        break;
    case Cyan:                  r = 0;          g = 255;        b = 255;        break;
    case Magenta:               r = 255;        g = 000;        b = 255;        break;
    case Yellow:                r = 255;        g = 255;        b = 000;        break;
    case Lime:                  r = 0;          g = 128;        b = 000;        break;
    case Water:                 r = 064;        g = 164;        b = 223;        break;
    case Plastic:               r = 129;        g = 129;        b = 126;        break;
    case Glass:                 r = 156;        g = 229;        b = 227;        break;
    case Diamond:               r = 241;        g = 247;        b = 251;        break;
    case Iron:                  r = 90;         g = 98;         b = 102;        break;
    case Copper:                r = 191;        g = 105;        b = 053;        break;
    case Gold:                  r = 255;        g = 215;        b = 000;        break;
    case Aluminum:              r = 132;        g = 135;        b = 137;        break;
    case Silver:                r = 192;        g = 192;        b = 192;        break;
    case Deepskyblue:           r = 000;        g = 191;        b = 255;        break;
    case Lightskyblue:          r = 135;        g = 206;        b = 255;        break;
    case Mistyrose:             r = 255;        g = 228;        b = 225;        break;
    case Burlywood:             r = 222;        g = 184;        b = 135;        break;
    case Violet:                r = 238;        g = 130;        b = 238;        break;
    case Whitesmoke:            r = 245;        g = 245;        b = 245;        break;
    case Tan:                   r = 210;        g = 180;        b = 140;        break;
    case Lightgray:             r = 211;        g = 211;        b = 211;        break;
    case Lightsteelblue:        r = 176;        g = 196;        b = 222;        break;
    case Yellowgreen:           r = 154;        g = 205;        b = 050;        break;
    case Orange:                r = 255;        g = 165;        b = 000;        break;
    case Coral:                 r = 255;        g = 127;        b = 80;         break;
    case Fuchsia:               r = 255;        g = 000;        b = 128;        break;
    case Dodgerblue:            r = 30;         g = 144;        b = 255;        break;
    case Plum:                  r = 142;        g = 69;         b = 133;        break;
    case Limegreen:             r = 50;         g = 205;        b = 050;        break;
    case Olive:                 r = 128;        g = 128;        b = 000;        break;
    case Darkmagenta:           r = 139;        g = 000;        b = 139;        break;
    case Gray:                  r = 128;        g = 128;        b = 128;        break;
    case Dimgray:               r = 000;        g = 105;        b = 105;        break;
    case Brown:                 r = 165;        g = 42;         b = 42;         break;
    case Darkslategray:         r = 47;         g = 79;         b = 79;         break;
    case Firebrick:             r = 178;        g = 34;         b = 34;         break;
    case Sienna:                r = 160;        g = 82;         b = 45;         break;
    case Maroon:                r = 128;        g = 000;        b = 0;          break;
    case Darkblue:              r = 000;        g = 000;        b = 139;        break;
    case Navy:                  r = 000;        g = 000;        b = 128;        break;
    default:
        r = g = b = 0;
    }
    return Glui_Color(r, g, b, 255);
}

unsigned int Glui_Color::ColorToUInt(Glui_Color color)
{
    unsigned int res = 0;
    res = color.R;    res <<= 8;
    res += color.G;   res <<= 8;
    res += color.B;   res <<= 8;
    res += color.A;   
    return res;    
}

Glui_Color Glui_Color::UIntToColor(unsigned int intValue)
{
    BYTE r,g,b,a;
    a = intValue & 255; intValue >>= 8;
    b = intValue & 255; intValue >>= 8;
    g = intValue & 255; intValue >>= 8;
    r = intValue & 255;
    return Glui_Color(r,g,b,a);
}
} // namespace GLUI