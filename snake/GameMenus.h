#pragma once

#include "LvlManager.h"
#include "MenuByList.h"

struct
{
	bool choiceMain()
	{
		mbl::MenuByList main_m("SNAKE", {
			"Play",
			"Setting",
			"Top list",
			"Exit",
		});
		enum
		{
			PLAY,
			SETT,
			TOP,
			EXIT
		};

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
	bool choiceSett()
	{
		mbl::MenuByList settings_m("SETTINGS", {
			"In developing 1",
			"In developing 2",
			"In developing 3",
			"Back",
		});
		enum
		{
			IN_DEV_1,
			IN_DEV_2,
			IN_DEV_3,
			BACK
		};

		while (true)
		{
			switch (settings_m.getChoice())
			{
			case IN_DEV_1: break;
			case IN_DEV_2: break;
			case IN_DEV_3: break;
			case BACK: return true;
			}
		}
	}
	int choiceLvl(LvlManager& lvls)
	{
		mbl::MenuByList lvlsel_m("CHOOSE LEVEL", {
			"-",
			"-",
			"-",
			"Next",
			"Back",
			"Cancel"
		});
		enum
		{
			LVL_1,
			LVL_2,
			LVL_LAST,
			NEXT,
			BACK,
			CANCEL,
		};

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
			case BACK: if (page > 0) page--; break;
			case CANCEL: return EOF;
			}
		}
	}
	bool choiceRes()
	{
		mbl::MenuByList restart_m("GAME OVER", {
			"Try again",
			"Back",
		});
		enum
		{
			TRY,
			BACK
		};

		while (true)
		{
			switch (restart_m.getChoice())
			{
			case TRY: return true;
			case BACK: return false;
			}
		}
	}
} Menus;