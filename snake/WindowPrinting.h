#pragma once

#include <string>
#include <windows.h>

using namespace std;

namespace WIN
{
	const int WIDTH = 120;
	const int HEIGHT = 60;
	const int LENGTH = WIDTH * HEIGHT;
}

namespace wp
{
	class Img
	{
		char _img[WIN::LENGTH] = {};
		
	public:
		Img() = default;

		template <class T>
		void addStr(T _img, COORD coord = {0, 0})
		{
			int poss = coord.X + coord.Y * WIN::WIDTH;
			for (int i = 0, y = 0; _img[i] != '\0'; i++, y++)
				this->_img[i + poss] = _img[i];
		}

		void setCh(const char _img, COORD coord = { 0, 0 })
		{
			this->_img[coord.X + coord.Y * WIN::WIDTH] = _img;
		}

		void set(const Img& _img, COORD coord = { 0, 0 })
		{
			int poss = coord.X + coord.Y * WIN::WIDTH;

			for (int y = 0; y < WIN::HEIGHT; y++)
				for (int x = 0; x < WIN::WIDTH; x++)
					(*this)[x][y] = 0;
		}

		operator const char* ()
		{
			return _img;
		}

		char* operator [] (int index)
		{
			return &_img[index];
		}
	};

	class 
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD dwBytesWritten = NULL;

	public:
		void fixSize(const int _w, const int _h)
		{
			_COORD coord;
			coord.X = _w;
			coord.Y = _h;
			_SMALL_RECT Rect;
			Rect.Top = 0;
			Rect.Left = 0;
			Rect.Bottom = _h - 1;
			Rect.Right = _w - 1;
			HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleScreenBufferSize(Handle, coord);
			SetConsoleWindowInfo(Handle, TRUE, &Rect);
		}

		void set_screen(Img& _img)
		{		
			WriteConsoleOutputCharacterA(
				hStdOut,
				_img,
				WIN::LENGTH,
				{NULL, NULL},
				&dwBytesWritten
			);
		}
		
	} Window;
}