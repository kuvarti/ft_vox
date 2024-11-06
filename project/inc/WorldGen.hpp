#pragma once
#include "Voxel.hpp"

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
		_len.x= x;
		_len.y= y;
	}
	~WorldGen()
	{
		for (int i = 0; i < _len.x; ++i)
		{
			delete[] _map[i];
		}
		delete[] _map;
	}

	Voxel &GetVoxelByLocalCoordinate(glm::vec2 v) const
	{
		// if (v.Get_x() > 15 || v.Get_x() < 0 || v.Get_y() > 15 || v.Get_y() < 0)
		// 	return Voxel(0,0,0);
		return _map[(int)v.x][(int)v.y];
	}
	Voxel &GetVoxelByLocalCoordinate(size_t x, size_t y) const
	{
		// if (x > 15 || y > 15)
		// 	return Voxel(0,0,0);
		return _map[x][y];
	}

protected:
	virtual void Generate(glm::vec2) = 0;
	void SetVoxelByLocalCoordinaate(glm::vec2 v, Voxel voxel)
	{
		_map[(int)v.x][(int)v.y] = voxel;
	}
	glm::vec2 GetLength() const
	{
		return _len;
	}

private:
	Voxel **_map;
	glm::vec2 _len;
};

class TerrainGen : virtual public WorldGen
{
public:
	TerrainGen(glm::vec2);
	~TerrainGen() {}

protected:
	void Generate(glm::vec2) override;
};

class CaveGen : virtual public WorldGen
{
public:
	CaveGen(glm::vec2);
	~CaveGen() {}

protected:
	void Generate(glm::vec2) override;

private:
	void SetFaces(_CAVE_LIST &, int *, unsigned char);
	void SetFaces(_CAVE_LIST &, _CAVE_LIST &, unsigned char, unsigned char);
	_CAVE_LIST SeperateCaves(int *, size_t);
	int *GetColumns(double, double, double);
};