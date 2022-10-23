#pragma once

#include <string>
#include <conio.h>
#include "WindowPrinting.h"

using namespace std;

namespace mbl
{
	enum
	{
		NEXT_SELECT = 's',
		PREVIOUS_SELECT = 'w',
		ENTER_BUTT = 13
	};

	class MenuByList
	{
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
		static void enterPause();
	};
}