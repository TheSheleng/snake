#pragma once

#include <fstream>
#include <thread>
#include "WindowPrinting.h"
#include "GameExcept.h"
#include "Objects.h"

using namespace std;
using namespace objs;

class
{
	Obj* objs[WIN::WIDTH][WIN::HEIGHT] = {};
	Snake* snake = nullptr;

	short spawnX = NULL;
	short spawnY = NULL;

	void spawnFood()
	{
		COORD temp;
		do temp = { (short)(rand() % WIN::WIDTH), (short)(rand() % WIN::HEIGHT) };
		while (objs[temp.X][temp.Y] != nullptr);
		objs[temp.X][temp.Y] = new objs::Food;
	}
	void spawnSnake(unsigned int size = 3) 
	{
		snake = new Snake;

		snake->Head.loc.X = spawnX;
		snake->Head.loc.Y = spawnY;

		objs[spawnX][spawnY] = &snake->Head;

		for (int i = 0; i < size; i++) snake->grow_up();
	}
	void diedSnake()
	{
		while (snake->body.size() > 0)
		{
			objs[snake->body.front().loc.X][snake->body.front().loc.Y] = nullptr;
			snake->body.pop();
		}
		objs[snake->Head.loc.X][snake->Head.loc.Y] != nullptr;

		delete snake;
	}
	void clearMap() 
	{
		diedSnake();
		for (short y = 0; y < WIN::HEIGHT; y++)
			for (short x = 0; x < WIN::WIDTH; x++)
				if (objs[x][y] != nullptr)
				{
					delete[] objs[x][y];
					objs[x][y] = nullptr;
				}
	}

	void snakeBodyDisplace()
	{
		//"Поджатие" хвоста
		if (snake->body.size() >= snake->getLen())
		{
			objs[snake->body.front().loc.X][snake->body.front().loc.Y] = nullptr;
			snake->body.pop();
		}

		//"Скачёк" телом
		snake->body.emplace(snake->Head.loc.X, snake->Head.loc.Y);
		objs[snake->Head.loc.X][snake->Head.loc.Y] = &snake->body.back();
	}
	bool snakeHeadMove()
	{
		//Изменение координат головы
		snake->Head.move();

		//Попытка телепорта
		if (!GameRule.tel_exec(snake->Head.loc.X, snake->Head.loc.Y)) return false;

		//Возможная коллизия
		if (objs[snake->Head.loc.X][snake->Head.loc.Y] != nullptr)
			switch (objs[snake->Head.loc.X][snake->Head.loc.Y]->getTexture())
			{
			//Препядствия
			case TXTRS::SEGMENT:
			case TXTRS::WALL: return false;

			//Еда
			case TXTRS::FOOD:
				//удаление с карты
				delete[] objs[snake->Head.loc.X][snake->Head.loc.Y];
				objs[snake->Head.loc.X][snake->Head.loc.Y] = nullptr;

				spawnFood();
				snake->grow_up();
				break;
			}

		//Запись на курту
		objs[snake->Head.loc.X][snake->Head.loc.Y] = &snake->Head;

		return true;
	}

public:
	const int gameOverPause = 500;

	class
	{
		bool telT(short& _x, short& _y)
		{
			if (_x < 0) _x = WIN::WIDTH - 1;
			else if (_x >= WIN::WIDTH) _x = 0;
			else if (_y < 0) _y = WIN::HEIGHT - 1;
			else if (_y >= WIN::HEIGHT) _y = 0;

			return true;
		}
		bool telF(short& _x, short& _y)
		{
			return !(_x < 0 || _y < 0 || _x >= WIN::WIDTH || _y < 0 || _y >= WIN::HEIGHT);
		}

		enum DELAY
		{
			DL_1 = 500,
			DL_2 = 300,
			DL_3 = 100
		} delay = DL_3;
		bool tel = true;

	public:
		void chDl()
		{
			switch (delay)
			{
			case DL_1: delay = DL_2; break;
			case DL_2: delay = DL_3; break;
			case DL_3: delay = DL_1; break;
			}
		}
		DELAY getDl() { return delay; }

		void chTel()
		{
			tel = !tel;
		}
		bool getTel()
		{
			return tel;
		}
		bool tel_exec(short& _x, short& _y)
		{
			if (tel) return telT(_x, _y);
			else return telF(_x, _y);
		}
	} GameRule;

	void lvlRead(string LvlName)
	{
		ifstream lvlFile("levels\\" + LvlName);

		if (lvlFile.is_open())
		{
			bool headWritten = false;

			short x = 0, y = 0;
			while (!lvlFile.eof())
			{
				switch (lvlFile.get())
				{
				case TXTRS::WALL: objs[x++][y] = new Wall; break;
				case TXTRS::HEAD:
					//Обязательно должна быть только одна точка старта
					if (!headWritten)
					{
						spawnX = x++;
						spawnY = y;

						headWritten = true;
					}
					else throw ge::GameExcept("There is more than one starting position on the map.");
					break;

				//Разные смещения координат
				case TXTRS::SPACE: x++; break;
				case '\n':
				case EOF:
					x = 0; y++;
					break;

				default: throw ge::GameExcept("Unknown object.");
				}

				//Игнорирование объектов за картой
				if (x >= WIN::WIDTH)
				{
					char ch = lvlFile.get();
					while (ch != '\n' && ch != EOF)
						ch = lvlFile.get();
					x = 0; y++;
				}
				else if (y >= WIN::HEIGHT) break;
			}

			if (!headWritten) throw ge::GameExcept("There is no starting point on the map.");

			lvlFile.close();
		}
		else throw ge::GameExcept("File not found.");
	}
	void startGame(unsigned int foodQty = 30)
	{
		spawnSnake();

		srand(time(NULL));
		for (int i = 0; i < foodQty; i++) spawnFood();

		//Создание потока для ввода управления
		bool key_log = true;
		thread control([&]() { while (key_log) snake->Head.changeDir(); });

		while (teek());

		key_log = false;
		control.join();

		clearMap();
	}
	bool teek()
	{
		//Вывод и пауза
		PlayGround.print();
		Sleep(GameRule.getDl());

		//Движение змейки
		snakeBodyDisplace();
		if (!snakeHeadMove()) 
			return false;

		return true;
	}
	void print()
	{
		wp::Img screen;

		for (short y = 0; y < WIN::HEIGHT; y++)
			for (short x = 0; x < WIN::WIDTH; x++)
				if (objs[x][y] != nullptr)
					screen.setCh(objs[x][y]->getTexture(), {x, y});
				else screen.setCh(TXTRS::SPACE, {x, y});

		wp::Window.set_screen(screen);
	}
} PlayGround;