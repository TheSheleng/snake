#include "GameMenus.h"
#include "LvlManager.h"
#include "Game.h"

using namespace std;

bool main()
{
	wp::Window.fixSize(WIN::WIDTH, WIN::HEIGHT);

	Menus _menus;
	LvlManager lvlList;

	while (true)
		try 
		{
			if (_menus.choiceMain())
			{
				lvlList.analyzeFolder();
				int choose = _menus.choiceLvl(lvlList);

				if (choose != -1) PlayGround.startGame(lvlList[choose]);
			}
			else return true;
	}
	catch (ge::GameExcept& gex) { gex.errPrint(); }
}