#pragma once

template <class T>
class AsTwoDim
{
	T* arr;
	int width;
	int height;

public:
	AsTwoDim(int _w, int _h) : width(_w), height(_h)
	{
		arr = new T[width * height];
	}

	T* operator[] (int index)
	{
		return &(arr[index * height]);
	}

};