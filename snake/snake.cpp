#include "LvlManager.h"
#include "GameMenus.h"
#include "Game.h"

using namespace std;

int main()
{
	//Изменить размер окна
	{
		_COORD coord;
		coord.X = WIN::WIDTH;
		coord.Y = WIN::HEIGHT;
		_SMALL_RECT Rect;
		Rect.Top = 0;
		Rect.Left = 0;
		Rect.Bottom = WIN::HEIGHT - 1;
		Rect.Right = WIN::WIDTH - 1;
		HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleScreenBufferSize(Handle, coord);
		SetConsoleWindowInfo(Handle, TRUE, &Rect);
	}

	while (true)
		try 
		{
			//Быть в меню пока не запущенна игра
			if (Menus.choiceMain())
			{
				//Найти уровни дать выбор
				LvlManager lvlList;
				lvlList.analyzeFolder();
				int choose = Menus.choiceLvl(lvlList);

				if (choose != EOF) //Если уронь был выбран 
					//Играть уровень пока игрок не выйдет
					do 
					{ 
						PlayGround.lvlRead(lvlList[choose]);
						PlayGround.startGame(); 
						Sleep(PlayGround.gameOverPause); 
					}
					while (Menus.choiceRes());
			}
			else return true; //Выход
		}
	catch (ge::GameExcept& gex) { gex.errPrint(); }
}