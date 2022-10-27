#pragma once

#include <iostream>
#include <list>
#include <queue>

namespace objs
{
	class Obj
	{

	public:
		virtual char getTexture() = 0;
	};

	namespace TXTRS
	{
		const char SPACE = ' ';
		const char WALL = '#';
		const char FOOD = '*';
		const char SEGMENT = 'O';
		const char HEAD = '@';
	};

	class Wall : public Obj
	{


	public:
		virtual char getTexture() { return TXTRS::WALL; }
	};

	class Food : public Obj
	{


	public:
		virtual char getTexture() { return TXTRS::FOOD; }
	};

	class Entity : public Obj
	{

	public:
		COORD loc = {0, 0};
	};

	class Segment : public Entity
	{

	public:
		Segment(short _x, short _y) { loc = { _x, _y }; }

		virtual char getTexture() { return  TXTRS::SEGMENT; }
	};

	class Snake
	{
		enum KEYS
		{
			LEFT = 0x41,
			RIGHT = 0x44,
			UP = 0x57,
			DOWN = 0x53,
		};
		unsigned int Len = NULL;

	public:
		queue<Segment, list<Segment>> body;

		class : public objs::Entity
		{
			enum DIR
			{
				LEFT,
				RIGHT,
				UP,
				DOWN
			} Dir = RIGHT;

		public:
			virtual char getTexture() { return  TXTRS::HEAD; }
			virtual void move()
			{
				switch (Dir)
				{
				case LEFT: if(loc.X >= 0) --loc.X; break;
				case RIGHT:; if (loc.X < WIN::WIDTH) ++loc.X; break;
				case UP: ; if (loc.Y >= 0) --loc.Y; break;
				case DOWN: ; if (loc.Y < WIN::HEIGHT) ++loc.Y; break;
				}
			}
			void changeDir()
			{
				//switch (_getch())
				//{
				//case KEYS::LEFT: if (Dir != DIR::RIGHT) Dir = DIR::LEFT; break;
				//case KEYS::RIGHT: if (Dir != DIR::LEFT) Dir = DIR::RIGHT; break;
				//case KEYS::UP: if (Dir != DIR::DOWN) Dir = DIR::UP; break;
				//case KEYS::DOWN: if (Dir != DIR::UP) Dir = DIR::DOWN; break;
				//}

				if (GetAsyncKeyState(KEYS::LEFT)) if (Dir != DIR::RIGHT) Dir = DIR::LEFT;
				if (GetAsyncKeyState(KEYS::RIGHT)) if (Dir != DIR::LEFT) Dir = DIR::RIGHT;
				if (GetAsyncKeyState(KEYS::UP)) if (Dir != DIR::DOWN) Dir = DIR::UP;
				if (GetAsyncKeyState(KEYS::DOWN)) if (Dir != DIR::UP) Dir = DIR::DOWN;
			}
		} Head;

		unsigned int getLen() { return Len; }
		void grow_up() { Len++; }

		bool increased() { return body.size() < Len; }
	};
}