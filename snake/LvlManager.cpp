#include "LvlManager.h"

void LvlManager::addName(string name)
{
    string* temp = new string[namesQty + 1];

    for (int i = 0; i < namesQty; i++)
        temp[i] = lvlNames[i];
    temp[namesQty] = name;

    namesQty += 1;
    delete[] lvlNames;
    lvlNames = temp;
}

void LvlManager::analyzeFolder()
{
    LvlManager::~LvlManager();

    _finddata_t data = {};
    intptr_t hFile = _findfirst("levels\\*.map", &data);

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

string& LvlManager::operator[] (int index)
{
    return lvlNames[index];
}

int LvlManager::getQty()
{
    return namesQty;
}