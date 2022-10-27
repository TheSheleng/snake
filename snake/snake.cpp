#include "LvlManager.h"
#include "GameMenus.h"
#include "Game.h"

#include <iostream>

using namespace std;

int main()
{
	wp::Window.fixSize(WIN::WIDTH, WIN::HEIGHT);

	LvlManager lvlList;

	while (true)
		try 
		{
			if (Menus.choiceMain())
			{
				lvlList.analyzeFolder();
				int choose = Menus.choiceLvl(lvlList);

				if (choose != EOF)
				{
					do 
					{ 
						PlayGround.lvlRead(lvlList[choose]);
						PlayGround.startGame(); 
						Sleep(PlayGround.gameOverPause); 
					}
					while (Menus.choiceRes());
				}
			}
			else return true;
	}
	catch (ge::GameExcept& gex) { gex.errPrint(); }
}