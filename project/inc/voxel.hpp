#pragma once
#include "vector2D.hpp"
#include <list>

class Voxel
{
public:
	Voxel() { _x = 0; _y = 0; _z = 0; }
	Voxel(int x, int y, int z){ _x = x; _y = y; _z = z; }
	Voxel (const Voxel &v){ _x = v._x; _y = v._y; _z = v._z; _caves = v._caves; }
	Voxel & operator=(const Voxel &v){ if (&v != this) 
		{ _x = v._x; _y = v._y; _z = v._z; _caves = v._caves; } return *this; };
	~Voxel() {
		while (!_caves.empty())
			_caves.pop_front();
	};

	void	AddCave(int min, int max) {
		_caves.emplace_back(min, max);
	}
	std::list<std::tuple<int, int>>	getCaves() {
		return _caves;
	}
	bool	IsCave(int z) {
		for (const auto& cave : _caves) {
			if (z >= std::get<0>(cave) && z <= std::get<1>(cave))
				return true;
		}
		return false;
	}

	int		Get_x() const { return _x; }
	int		Get_y() const { return _y; }
	int		Get_z() const { return _z; }
	Vector2D	Get_2dPos() const { return Vector2D(_x, _y); }

	void	Set_x(int x) { _x = x; }
	void	Set_y(int y) { _y = y; }
	void	Set_z(unsigned z) { _z = z; }
	void	Set_2dPos(int x, int y) { _x = x; _y = y; }
	void	Set_2dPos(Vector2D v) { _x = v.Get_x(); _y = v.Get_y(); }
private:
	int _x;
	int _y;
	int _z;
	std::list<std::tuple<int, int>> _caves;
};