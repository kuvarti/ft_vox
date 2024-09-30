#pragma once
#include "voxel.hpp"

class WorldGen
{
public:
	WorldGen(int x, int y)
	{
		_map = new Voxel *[x];
		for (int i = 0; i < x; ++i)
		{
			_map[i] = new Voxel[y];
		}
		_len.Set_x(x);
		_len.Set_y(y);
	}
	~WorldGen()
	{
		for (int i = 0; i < _len.Get_x(); ++i)
		{
			delete[] _map[i];
		}
		delete[] _map;
	}

	Voxel GetVoxelByLocalCoordinate(Vector2D v) const
	{
		return _map[(int)v.Get_x()][(int)v.Get_y()];
	}
	Voxel GetVoxelByLocalCoordinate(int x, int y) const
	{
		return _map[x][y];
	}

protected:
	virtual void Generate(Vector2D) = 0;
	void SetVoxelByLocalCoordinaate(Vector2D v, Voxel voxel)
	{
		_map[(int)v.Get_x()][(int)v.Get_y()] = voxel;
	}
	Vector2D GetLength() const
	{
		return _len;
	}

private:
	Voxel **_map;
	Vector2D _len;
};

class TerrainGen : virtual public WorldGen
{
public:
	TerrainGen(Vector2D);
	~TerrainGen() {}

protected:
	void Generate(Vector2D) override;
};

class CaveGen : virtual public WorldGen
{
public:
	CaveGen(Vector2D);
	~CaveGen() {}

protected:
	void Generate(Vector2D) override;
};