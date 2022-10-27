#pragma once

#include "LvlManager.h"
#include "MenuByList.h"
#include "Game.h"

struct
{
	bool choiceMain()
	{
		mbl::MenuByList main_m("SNAKE", {
			"Play",
			"Setting",
			"Exit",
		});
		enum
		{
			PLAY,
			SETT,
			EXIT
		};

		while (true)
		{
			switch (main_m.getChoice())
			{
			case PLAY: return true;
			case SETT: choiceSett(); break;
			case EXIT: return false;
			}
		}
	}
	bool choiceSett()
	{
		mbl::MenuByList settings_m("SETTINGS", {
			"Teleport: true",
			"Delay",
			"Back",
		});
		enum
		{
			TELEP,
			DELAY,
			BACK
		};

		while (true)
		{
			//����� �������� ���������
			string tel_s = "Teleport: ";
			tel_s += (PlayGround.GameRule.getTel() ? " true" : "false");
			settings_m.set(tel_s, TELEP);

			//����� �������� ��������
			string del_s = "Deley: ";
			del_s += to_string(PlayGround.GameRule.getDl());
			settings_m.set(del_s, DELAY);

			switch (settings_m.getChoice())
			{
			case TELEP: PlayGround.GameRule.chTel(); break;
			case DELAY: PlayGround.GameRule.chDl(); break;
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
			//��������
			const int FIRST_ON_PAGE = page * (LVL_LAST + 1);

			//����������� ��� ������
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