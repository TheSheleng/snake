#include "MenuByList.h"

wp::Img& mbl::MenuByList::render_m(const unsigned int& _sel)
{
    wp::Img screen;

    short str_num = 5;

    //Шапка
    const char* NAME_DECOR = "---===<*|||*>===---";
    screen.addStr(NAME_DECOR, { (short)(WIN::WIDTH - strlen(NAME_DECOR)) / 2, str_num });
    screen.addStr(mName, { (short)(WIN::WIDTH - mName.size()) / 2, str_num += 2 });
    screen.addStr(NAME_DECOR, { (short)(WIN::WIDTH - strlen(NAME_DECOR)) / 2, str_num += 2 });

    //Настройки вида кнопки
    const short INTERVAL = 7;
    const short BUTT_WIDTH = 17;
    const short SEL_SHIFT = 2;

    const short BUTT_LEFT = (WIN::WIDTH - BUTT_WIDTH) / 2;
    const short BUTT_RIGHT = BUTT_WIDTH + BUTT_LEFT - 1;

    //Кнопки

    str_num += INTERVAL / 2;
    for (short i = 0; i < size; i++)
    {
        bool selected = _sel == i;

        short height = i * INTERVAL + str_num;
        short sel_left = selected * SEL_SHIFT + BUTT_LEFT;
        short sel_right = selected * SEL_SHIFT + BUTT_RIGHT;

        //Шапка кнопки
        for (short w = 0; w < BUTT_WIDTH; w++)
            screen.setCh('#', { sel_left + w, height});
        height++;

        screen.setCh('#', { sel_left, height });
        screen.setCh('#', { sel_right, height });
        height++;

        //Середина кнопки
        screen.setCh('#', { sel_left, height });
        screen.addStr(list[i], { selected * SEL_SHIFT + (short)(WIN::WIDTH - list[i].size()) / 2, height });
        screen.setCh('#', { sel_right, height });
        height++;

        //Низ кнопки
        screen.setCh('#', { sel_left, height });
        screen.setCh('#', { sel_right, height });
        height++;
        for (short w = 0; w < BUTT_WIDTH; w++)
            screen.setCh('#', { sel_left + w, height });

    }

    return screen;
}

mbl::MenuByList::MenuByList(string mName, initializer_list<string> list)
{
    this->mName = mName;

    size = list.size();
    this->list = new string[size];

    for (int i = 0; i < size; i++)
        this->list[i] = list.begin()[i];
}

mbl::MenuByList::~MenuByList()
{
    delete[] list;
}

void mbl::MenuByList::set(string mName, int index)
{
    if (index >= 0 && index < size)
    {
        list[index] = mName;
    }
}

int mbl::MenuByList::getChoice()
{
    system("cls");

    int selected = 0;
    while (true)
    {
        wp::Window.set_screen(render_m(selected));

        char butt = _getch();
        switch (butt)
        {
        case NEXT_SELECT: if (selected < size - 1) selected++; break;
        case PREVIOUS_SELECT:if (selected > 0)selected--; break;
        case ENTER_BUTT: return selected;
        }
    }
}

void mbl::SAbility::enterPause()
{
    while (true) if (_getch() == ENTER_BUTT) break;
}