#ifndef CONFIGINI_H
#define CONFIGINI_H

#include <string>
#include <fstream>
#include <sstream>

//Класс конфигурации, который сохраняет данные настроек.
class ConfigINI
{
public:
	ConfigINI(const std::string& filename);
	~ConfigINI();
	//Очистить файл.
	void clear();
	//Получить строку по сектору и ключу настройки.
	std::string getOptionToString(const std::string& section,const std::string& key);
	//Получить число по сектору и ключу настройки.
	int getOptionToInt(const std::string& section,const std::string& key);

	unsigned int getOptionToUInt(const std::string& section,const std::string& key);
	//Добавить новую запись. Возвращает истину при удачной записи.
	bool addNewOption(const std::string& section,const std::string& key,const std::string& value);
	//Добавить новую запись. Возвращает истину при удачной записи.
	bool addNewOption(const std::string& section,const std::string& key,const int& value);

	bool addNewOption(const std::string& section,const std::string& key,const unsigned int& value);
	//Изменить значение. Возвращает истину при удачной записи.
	bool updateOption(const std::string& section,const std::string& key,const std::string& value);
	//Изменить значение. Возвращает истину при удачной записи.
	bool updateOption(const std::string& section,const std::string& key,const int& value);

	bool updateOption(const std::string& section,const std::string& key,const unsigned int& value);
private:
	std::string fname;
	std::ofstream fout;
	std::ifstream fin;
};

#endif // !CONFIGINI_H