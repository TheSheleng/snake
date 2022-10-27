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
    const string& operator[] (int index) const;

    int getQty() const;
};