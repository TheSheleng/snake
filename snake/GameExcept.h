#pragma once

#include <exception>
#include "MenuByList.h"

namespace ge
{
	class GameExcept
	{
		string ex;

	public:
		GameExcept(string ex);
		void errPrint();
	};
}