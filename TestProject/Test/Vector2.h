#pragma once

template <class T>
class Vector2
{
public:

	Vector2(T x, T y);
	T x;
	T y;
};

template <class T>
Vector2<T>::Vector2(T x, T y)
{
	this->x = x;
	this->y = y;
}

