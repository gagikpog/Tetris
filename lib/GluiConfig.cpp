#include "GluiConfig.h"

namespace GLUI
{
    using namespace Glui_Private;

    Glui_Config::Glui_Config(std::string file_name)
    {
        if (Open(file_name))
        {
            _is_open = true;
            _file_name = file_name;
        }
        else
            _is_open = false;
    }
    Glui_Config::Glui_Config()
    {
        _is_open = false;
        _file_name = "";
    }
    Glui_Config::~Glui_Config()
    {
        Data.clear();
    }
    bool Glui_Config::Open(std::string file_name)
    {
        if (file_name == "")
            file_name = _file_name;
        else
            _file_name = file_name;

        std::ifstream in;
        in.open(file_name);
        if (!in.is_open())
            return false;

        Data.clear();
        std::string text;
        unsigned int count;
        in >> text;

        if (text != "GCF")
            return false;
        string_int temp;
        while (true)
        {
            if (in >> text)
            {
                temp.Text = text;
                in >> count;
                temp.Count = count;
                Data.push_back(temp);
                //	std::cout << "in   " << temp.Text << "  " << temp.Count<<std::endl;
            }
            else
                break;
        }
        in.close();
        return true;
    }
    bool Glui_Config::Get_count(std::string name, int &count)
    {
        for (int i = 0; i < Data.size(); i++)
        {
            if (name == Data[i].Text)
            {
                count = Data[i].Count;
                return true;
            }
        }
        return false;
    }
    bool Glui_Config::Get_color(std::string name, Glui_Color &col)
    {
        for (int i = 0; i < Data.size(); i++)
        {
            if (name == Data[i].Text)
            {
                col.setUInt(Data[i].Count);
                return true;
            }
        }
        return false;
    }
    bool Glui_Config::Set_count(std::string name, int count, bool _save)
    {
        bool a(0);
        for (int i = 0; i < Data.size(); i++)
        {
            if (name == Data[i].Text)
            {
                Data[i].Count = count;
                a = 1;
                break;
            }
        }
        if (_save)
            Save();
        if (a)
            return true;
        return false;
    }
    bool Glui_Config::Set_color(std::string name, Glui_Color col, bool _save)
    {
        bool a(0);
        for (int i = 0; i < Data.size(); i++)
        {
            if (name == Data[i].Text)
            {

                Data[i].Count = col.getUInt();
                a = 1;
                break;
            }
        }
        if (_save)
            Save();
        if (a)
            return true;
        return false;
    }
    bool Glui_Config::Save(std::string file_name)
    {
        if (file_name == "")
            file_name = _file_name;
        std::ofstream out;
        out.open(file_name);
        if (!out.is_open())
            return false;
        _is_open = true;

        std::sort(Data.begin(), Data.end(), [](string_int a, string_int b) { return a.Text < b.Text; });
        out << "GCF\n";

        for (int i = 0; i < Data.size(); i++)
        {
            out << Data[i].Text << " " << Data[i].Count << std::endl;
            //	std::cout<<"out  " << Data[i].Text << " " << Data[i].Count << std::endl;
        }
        out.close();
        return true;
    }
    bool Glui_Config::Add_item(std::string name, int count)
    {
        for (int i = 0; i < Data.size(); i++)
        {
            if (name == Data[i].Text)
            {
                return false;
            }
        }
        string_int temp;
        temp.Count = count;
        temp.Text = name;
        Data.push_back(temp);
        return true;
    }
    bool Glui_Config::Erase_item(std::string name)
    {
        for (int i = 0; i < Data.size(); i++)
        {
            if (Data[i].Text == name)
            {
                Data.erase(Data.begin() + i);
            }
        }
        return true;
    }
    bool Glui_Config::Clear()
    {
        Data.clear();
        return 1;
    }
} // namespace GLUI