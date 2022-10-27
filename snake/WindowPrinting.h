#pragma once

#include <windows.h>

using namespace std;

namespace WIN //��������� ����
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
		void addStr(T _img, COORD coord = {0, 0}) //������ ������
		{
			int poss = coord.X + coord.Y * WIN::WIDTH;
			for (int i = 0, y = 0; _img[i] != '\0'; i++, y++)
				this->_img[i + poss] = _img[i];
		}
		void setCh(const char _img, COORD coord = { 0, 0 }) //������ �������
		{
			this->_img[coord.X + coord.Y * WIN::WIDTH] = _img;
		}
		operator const char* () const //����� �����������
		{
			return _img;
		}
	};

	class 
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD dwBytesWritten = NULL;

	public:
		//����� ��������
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