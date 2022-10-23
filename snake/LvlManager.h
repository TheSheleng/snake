#pragma once

#include "GameExcept.h"

#include <string>
#include <io.h>

using namespace std;

class LvlManager
{
    int namesQty = 0;
    string* lvlNames = nullptr;

    void addName(string name);

public:
    ~LvlManager();

    void analyzeFolder();
    string& operator[] (int index);
    int getQty();
};