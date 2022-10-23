#pragma once

#include "LvlManager.h"
#include "MenuByList.h"

class Menus
{
	mbl::MenuByList main_m;
	enum
	{
		PLAY,
		SETT,
		TOP,
		EXIT
	};
	mbl::MenuByList settings_m;
	enum
	{
		IN_DEV_1,
		IN_DEV_2,
		IN_DEV_3,
		BACK_SETT
	};
	mbl::MenuByList lvlsel_m;
	enum
	{
		LVL_1,
		LVL_2,
		LVL_LAST,
		NEXT,
		BACK_LVL,
		CANCEL,
	};

public:
	Menus();
	bool choiceMain();
	bool choiceSett();
	int choiceLvl(LvlManager& lvls);
};