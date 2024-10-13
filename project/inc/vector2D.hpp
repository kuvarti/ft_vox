#pragma once

#include <list>
#include <tuple>

class Vector2D
{
public:
	Vector2D() { _x = 0; _y = 0; }
	Vector2D(float x, float y){ _x = x; _y = y; }
	Vector2D (const Vector2D &v){ _x = v._x; _y = v._y; }
	Vector2D & operator=(const Vector2D &v){ if (&v != this)
		{ _x = v._x; _y = v._y; } return *this; };
	~Vector2D() { };

	float	Get_x() const { return _x; }
	float	Get_y() const { return _y; }
	void	Set_x(float x) { _x = x; }
	void	Set_y(float y) { _y = y; }
private:
	float _x;
	float _y;
};
