#include "LvlManager.h"

void LvlManager::addName(string name)
{
    string* temp = new string[namesQty + 1];

    //Копирование по временному указателю + новый элем.
    for (int i = 0; i < namesQty; i++)
        temp[i] = lvlNames[i];
    temp[namesQty] = name;

    //Перезапись с очисткой
    namesQty++;
    delete[] lvlNames;
    lvlNames = temp;
}

void LvlManager::analyzeFolder()
{
    //Очитска перед созданием
    LvlManager::~LvlManager();

    //Поиск в директории и нужным расширением
    _finddata_t data = {};
    intptr_t hFile = _findfirst("levels\\*.map", &data);

    //Допавление всех имён файлов
    if (hFile != EOF)
    {
        do addName(data.name);
        while (_findnext(hFile, &data) != EOF);
        _findclose(hFile);
    }
    else throw ge::GameExcept("Directory with levels not found or it is empty");
}

LvlManager::~LvlManager()
{
    namesQty = 0;
    delete[] lvlNames;
    lvlNames = nullptr;
}

const string& LvlManager::operator[] (int index) const
{
    return lvlNames[index];
}

int LvlManager::getQty() const
{
    return namesQty;
}