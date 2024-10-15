#include "chunk.hpp"
#include "ProceduralGenerationAlgorithms.hpp"
#include "iostream"
#include <chrono>

Chunk::Chunk() : TerrainGen(Vector2D(CHUNK_SIZE, CHUNK_SIZE)),
				 CaveGen(Vector2D(CHUNK_SIZE, CHUNK_SIZE)),
				 WorldGen(CHUNK_SIZE, CHUNK_SIZE)
{
	_startPoint.Set_x(0);
	_startPoint.Set_y(0);
	_length = CHUNK_SIZE;

	std::cout << "Chunk::Chunk() Called" << std::endl;
}

Chunk::Chunk(Vector2D startPoint) : TerrainGen(Vector2D(CHUNK_SIZE, CHUNK_SIZE)),
									CaveGen(Vector2D(CHUNK_SIZE, CHUNK_SIZE)),
									WorldGen(CHUNK_SIZE, CHUNK_SIZE)
{
	_startPoint = startPoint;
	_length = CHUNK_SIZE;

	this->Generate(_startPoint);
}

Chunk::Chunk(float x, float y) : TerrainGen(Vector2D(CHUNK_SIZE, CHUNK_SIZE)),
								 CaveGen(Vector2D(CHUNK_SIZE, CHUNK_SIZE)),
								 WorldGen(CHUNK_SIZE, CHUNK_SIZE)
{
	_startPoint.Set_x(x);
	_startPoint.Set_y(y);
	_length = CHUNK_SIZE;

	this->Generate(_startPoint);
	PrintVoxelInfo();
}

Chunk::~Chunk()
{
}

void Chunk::ChangeStartPosition(Vector2D v)
{
	_startPoint = v;
	this->Generate(_startPoint);
}

Voxel Chunk::GetVoxelbyGlobalCoordinate(Vector2D v) const
{
	if (v.Get_x() > _startPoint.Get_x() + _length || v.Get_x() < _startPoint.Get_x())
		return Voxel(0, 0, 0);
	else if (v.Get_y() > _startPoint.Get_y() + _length || v.Get_y() < _startPoint.Get_y())
		return Voxel(0, 0, 0);
	else
		return GetVoxelByLocalCoordinate(v.Get_x() - _startPoint.Get_x(), v.Get_y() - _startPoint.Get_y());
}

Voxel Chunk::GetVoxelbyGlobalCoordinate(int x, int y) const
{
	if (x > _startPoint.Get_x() + _length || x < _startPoint.Get_x())
		return Voxel(0, 0, 0);
	else if (y > _startPoint.Get_y() + _length || y < _startPoint.Get_y())
		return Voxel(0, 0, 0);
	else
		return GetVoxelByLocalCoordinate(x - _startPoint.Get_x(), y - _startPoint.Get_y());
}

void mapfree(int **m, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		delete[] m[i];
	}
	delete[] m;
}

int GetSurroundingWallCount(int gridX, int gridY, int gridZ, int ***map)
{
	int wallCount = 0;
	for (int neighborX = gridX - 1; neighborX <= gridX + 1; ++neighborX)
	{
		for (int neighborY = gridY - 1; neighborY <= gridY + 1; ++neighborY)
		{
			for (int neighborZ = gridZ - 1; neighborZ <= gridZ + 1; ++neighborZ)
			{
				if (neighborX >= 0 && neighborX < GRID_SIZE && neighborY >= 0 && neighborY < GRID_SIZE && neighborZ >= 0 && neighborZ < GRID_SIZE)
				{
					if (neighborX != gridX || neighborY != gridY || neighborZ != gridZ)
					{
						wallCount += map[neighborX][neighborY][neighborZ];
					}
				}
				else
				{
					wallCount++;
				}
			}
		}
	}
	return wallCount;
}

void SmoothMap(int ***map)
{
	for (int x = 0; x < GRID_SIZE; ++x)
	{
		for (int y = 0; y < GRID_SIZE; ++y)
		{
			for (int z = 0; z < GRID_SIZE; ++z)
			{
				int surroundingWallCount = GetSurroundingWallCount(x, y, z, map);
				if (surroundingWallCount > 4)
					map[x][y][z] = 1;
				else if (surroundingWallCount < 4)
					map[x][y][z] = 0;
			}
		}
	}
}

int ***Chunk::_GenerateCave()
{
	int ***map = new int **[GRID_SIZE];
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		map[i] = new int *[GRID_SIZE];
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			map[i][j] = new int[GRID_SIZE];
			for (int k = 0; k < GRID_SIZE; ++k)
			{
				map[i][j][k] = (rand() % 2);
			}
		}
	}

	for (int i = 0; i < 5; ++i)
	{
		SmoothMap(map);
	}

	return map;
}

void Chunk::PrintVoxelInfo()
{
	// nothing to do here
}