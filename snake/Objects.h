#pragma once

#include <list>
#include <queue>

namespace objs
{
	struct Obj
	{
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

	struct Entity : public Obj
	{
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
		static enum KEYS
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
			static enum DIR
			{
				LEFT,
				RIGHT,
				UP,
				DOWN
			}; 
			DIR Dir = RIGHT;
			DIR lastMove = Dir;

		public:
			virtual char getTexture() { return  TXTRS::HEAD; }
			virtual void move()
			{
				switch (Dir)
				{
				case LEFT: if (loc.X >= 0) { --loc.X; lastMove = DIR::LEFT; break; }
				case RIGHT:; if (loc.X < WIN::WIDTH) { ++loc.X; lastMove = DIR::RIGHT; break; }
				case UP:; if (loc.Y >= 0) { --loc.Y; lastMove = DIR::UP; break; }
				case DOWN:; if (loc.Y < WIN::HEIGHT) { ++loc.Y; lastMove = DIR::DOWN; break; }
				}
			}
			void changeDir()
			{
				if (GetAsyncKeyState(KEYS::LEFT)) if (lastMove != DIR::RIGHT) Dir = DIR::LEFT;
				if (GetAsyncKeyState(KEYS::RIGHT)) if (lastMove != DIR::LEFT) Dir = DIR::RIGHT;
				if (GetAsyncKeyState(KEYS::UP)) if (lastMove != DIR::DOWN) Dir = DIR::UP;
				if (GetAsyncKeyState(KEYS::DOWN)) if (lastMove != DIR::UP) Dir = DIR::DOWN;
			}
		} Head;

		unsigned int getLen() { return Len; }
		void grow_up() { Len++; }
	};
}