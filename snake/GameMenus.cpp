#include "GameMenus.h"

Menus::Menus() :
	main_m("SNAKE", {
		"Play",
		"Setting",
		"Top list",
		"Exit",
	}),
	settings_m("SETTINGS", {
		"In developing 1",
		"In developing 2",
		"In developing 3",
		"Back",
	}),
	lvlsel_m("CHOOSE LEVEL", {
		"lvl name",
		"lvl name 2",
		"lvl name 3",
		"Next",
		"Back",
		"Cancel"
	})
{}

bool Menus::choiceMain()
{
	while (true)
	{
		switch (main_m.getChoice())
		{
		case PLAY: return true;
		case SETT: choiceSett(); break;
		case TOP: break; 
		case EXIT: return false;
		}
	}
}

bool Menus::choiceSett()
{
	while (true)
	{
		switch (settings_m.getChoice())
		{
		case IN_DEV_1: break;
		case IN_DEV_2: break;
		case IN_DEV_3: break;
		case BACK_SETT: return true;
		}
	}
}

int Menus::choiceLvl(LvlManager& lvls)
{
	const int LAST_PAGE = lvls.getQty() / (LVL_LAST + 1);
	int page = 0;
	while (true)
	{
		const int FIRST_ON_PAGE = page * (LVL_LAST + 1);

		lvlsel_m.set(FIRST_ON_PAGE + LVL_1 < lvls.getQty() ? lvls[FIRST_ON_PAGE + LVL_1] : "-", LVL_1);
		lvlsel_m.set(FIRST_ON_PAGE + LVL_2 < lvls.getQty() ? lvls[FIRST_ON_PAGE + LVL_2] : "-", LVL_2);
		lvlsel_m.set(FIRST_ON_PAGE + LVL_LAST < lvls.getQty() ? lvls[FIRST_ON_PAGE + LVL_LAST] : "-", LVL_LAST);

		switch (lvlsel_m.getChoice())
		{
		case LVL_1: return FIRST_ON_PAGE + LVL_1;
		case LVL_2: return FIRST_ON_PAGE + LVL_2 < lvls.getQty();
		case LVL_LAST: return FIRST_ON_PAGE + LVL_LAST;
		case NEXT: if (page < LAST_PAGE) page++; break;
		case BACK_LVL: if (page > 0) page--; break;
		case CANCEL: return -1;
		}
	}
}