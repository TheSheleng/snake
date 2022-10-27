#pragma once

#include <string>
#include <conio.h>
#include "WindowPrinting.h"

using namespace std;

namespace mbl
{
	class MenuByList
	{
		static enum
		{
			NEXT_SELECT = 0x53,
			PREVIOUS_SELECT = 0x57,
			ENTER_BUTT = 13
		};

		int size;
		string mName;
		string* list;

		wp::Img& render_m(const unsigned int& _sel);

	public:
		MenuByList(string mName, initializer_list<string> list);
		~MenuByList();

		void set(string mName, int index);
		int getChoice();
	};

	struct SAbility
	{
		static const int PAUSE_BUTT = 13;

		//Пауза до нажатия опр. клавиши
		static void enterPause();
	};
}