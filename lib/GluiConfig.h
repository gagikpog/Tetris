#include "GluiColor.h"
#include <vector>
#include <fstream>
#include <algorithm>

namespace GLUI
{
    namespace Glui_Private
    {
    struct string_int
        {
            std::string Text = "";
            std::string Text1 = "";
            unsigned int Count = 0;
            int Num = 0;
        };
    } // namespace Glui_Private

    //сохранение параметров (имя,значения)
    class Glui_Config
    {
    public:
        Glui_Config(std::string file_name);
        Glui_Config();
        ~Glui_Config();
        bool Open(std::string file_name = "");
        bool is_open() { return _is_open; }
        bool Get_count(std::string name, int &count);
        bool Get_color(std::string name, Glui_Color &col);
        bool Set_count(std::string name, int count, bool _save = 0);
        bool Set_color(std::string name, Glui_Color col, bool _save = 0);
        bool Save(std::string file_name = "");
        bool Add_item(std::string name, int count);
        bool Erase_item(std::string name);
        bool Clear();
        friend Glui_Color;

    private:
        std::vector<Glui_Private::string_int> Data;
        bool _is_open;
        std::string _file_name;
    };
} // namespace GLUI