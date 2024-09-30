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
		return Voxel(0,0,0);
	else if(v.Get_y() > _startPoint.Get_y() + _length || v.Get_y() < _startPoint.Get_y())
		return Voxel(0,0,0);
	return GetVoxelByLocalCoordinate(Vector2D(((int)_startPoint.Get_x() % _length) + v.Get_x(),
											  ((int)_startPoint.Get_y() % _length) + v.Get_y()));
}

Voxel Chunk::GetVoxelbyGlobalCoordinate(int x, int y) const
{
	if (x > _startPoint.Get_x() + _length || x < _startPoint.Get_x())
		return Voxel(0,0,0);
	else if(y > _startPoint.Get_y() + _length || y < _startPoint.Get_y())
		return Voxel(0,0,0);
	return GetVoxelByLocalCoordinate(Vector2D(((int)_startPoint.Get_x() % _length) + x,
											  ((int)_startPoint.Get_y() % _length) + y));
}

void mapfree(int **m, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		delete[] m[i];
	}
	delete[] m;
}

int GetSurroundingWallCount(int gridX, int gridY, int gridZ, int ***map)
{
	int wallCount = 0;

	// X, Y ve Z çevresindeki hücreleri kontrol et
	for (int neighbourX = gridX - 1; neighbourX <= gridX + 1; neighbourX++)
	{
		for (int neighbourY = gridY - 1; neighbourY <= gridY + 1; neighbourY++)
		{
			for (int neighbourZ = gridZ - 1; neighbourZ <= gridZ + 1; neighbourZ++)
			{
				if (neighbourZ < 0 || neighbourZ > 70)
					wallCount++;
				else if (neighbourX != gridX || neighbourY != gridY || neighbourZ != gridZ)
					wallCount += map[neighbourX][neighbourY][neighbourZ];
			}
		}
	}
	return wallCount;
}

void SmoothMap(int ***map)
{
	for (size_t x = 1; x <= 16; x++)
	{
		for (size_t y = 1; y <= 16; y++)
		{
			for (size_t z = 0; z < 70; z++)
			{
				int neighbourWallTiles = GetSurroundingWallCount(x, y, z, map);
				if (neighbourWallTiles > 6)
					map[x][y][z] = 1;
				else if (neighbourWallTiles < 6)
					map[x][y][z] = 0;
			}
		}
	}
}

int ***Chunk::_GenerateCave()
{ // todo void

	auto startTime = std::chrono::high_resolution_clock::now();
	int ***map;
	map = new int **[18];
	for (size_t i = 0; i < 18; i++)
		map[i] = new int *[18];
	for (size_t i = 0; i < 18; i++)
	{
		for (size_t j = 0; j < 18; j++)
		{
			map[i][j] = new int[70];
		}
	}
	// Generates
	int **map1;
	for (size_t x = _startPoint.Get_x() - 1, i = 0; x < _startPoint.Get_x() + _length + 1; x++, i++)
	{
		map1 = cellular(x, _length + 2);
		int **map2;
		for (size_t y = _startPoint.Get_y() - 1, j = 0; y < _startPoint.Get_y() + _length + 1; y++, j++)
		{
			map2 = cellular(y, 1);
			for (size_t z = 0; z < 70; z++)
			{
				if (map1[i][z] == map2[0][z])
				{
					map[i][j][z] = map1[i][z];
				}
				else
				{
					map[i][j][z] = map1[i][z];
				}
			}
			delete[] map2[0];
			delete[] map2;
		}
		mapfree(map1, _length + 2);
	}
	SmoothMap(map);

	// Saving chunk datas
	for (size_t x = 0; x < _length; x++) // 0
	{
		for (size_t y = 0; y < _length; y++) // 0
		{
		}
	}

	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	std::cout << "Time taken: " << duration << " milliseconds" << std::endl;
	return map;
}

void Chunk::PrintVoxelInfo()
{
	Voxel _voxel;
	printf("Chunk (%d)-(%d):\n", (int)_startPoint.Get_x(), (int)_startPoint.Get_y());
	for (size_t x = 0; x < _length; x++)
	{
		for (size_t y = 0; y < _length; y++)
		{
			_voxel = GetVoxelByLocalCoordinate(x, y);
			printf("\tVoxel Local Pos: X:%ld, Y:%ld - Voxel Global Pos: (%d)-(%d)-(%d)\n",
				   x, y, _voxel.Get_x(), _voxel.Get_y(), _voxel.Get_z());
		}
	}
}