#pragma once

namespace ent
{
	class Entity
	{
		short _X;
		short _Y;

	public:
		void setX(short _x) { _X = _x; }
		void setY(short _y) { _Y = _y; }

		short getX() { return _X; }
		short getY() { return _Y; }
	};

}