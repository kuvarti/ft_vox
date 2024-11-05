#include "Chunk.hpp"
#include "ProceduralGenerationAlgorithms.hpp"
#include "iostream"
#include <chrono>
#include <tuple>

Chunk::Chunk() : TerrainGen(glm::vec2(CHUNK_SIZE, CHUNK_SIZE)),
				 CaveGen(glm::vec2(CHUNK_SIZE, CHUNK_SIZE)),
				 WorldGen(CHUNK_SIZE, CHUNK_SIZE)
{
	_startPoint.x = 0;
	_startPoint.y = 0;
	_length = CHUNK_SIZE;

	std::cout << "Chunk::Chunk() Called" << std::endl;
}

Chunk::Chunk(glm::vec2 startPoint) : TerrainGen(glm::vec2(CHUNK_SIZE, CHUNK_SIZE)),
									CaveGen(glm::vec2(CHUNK_SIZE, CHUNK_SIZE)),
									WorldGen(CHUNK_SIZE, CHUNK_SIZE)
{
	_startPoint = startPoint;
	_length = CHUNK_SIZE;

	this->Generate(_startPoint);
}

Chunk::Chunk(float x, float y) : TerrainGen(glm::vec2(CHUNK_SIZE, CHUNK_SIZE)),
								 CaveGen(glm::vec2(CHUNK_SIZE, CHUNK_SIZE)),
								 WorldGen(CHUNK_SIZE, CHUNK_SIZE)
{
	_startPoint.x = x;
	_startPoint.y = y;
	_length = CHUNK_SIZE;

	this->Generate(_startPoint);
}

Chunk::~Chunk()
{
}

void Chunk::ChangeStartPosition(glm::vec2 v)
{
	_startPoint = v;
	this->Generate(_startPoint);
}

Voxel Chunk::GetVoxelbyGlobalCoordinate(glm::vec2 v) const
{
	if (v.x > _startPoint.x + _length || v.x < _startPoint.x)
		return Voxel(0, 0, 0);
	else if (v.y > _startPoint.y + _length || v.y < _startPoint.y)
		return Voxel(0, 0, 0);
	else
		return GetVoxelByLocalCoordinate(v.x - _startPoint.x, v.y - _startPoint.y);
}

Voxel Chunk::GetVoxelbyGlobalCoordinate(int x, int y) const
{
	if (x > _startPoint.x + _length || x < _startPoint.x)
		return Voxel(0, 0, 0);
	else if (y > _startPoint.y + _length || y < _startPoint.y)
		return Voxel(0, 0, 0);
	else
		return GetVoxelByLocalCoordinate(x - _startPoint.x, y - _startPoint.y);
}

void mapfree(int **m, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		delete[] m[i];
	}
	delete[] m;
}

int ***Chunk::_GenerateCave()
{

	auto startTime = std::chrono::high_resolution_clock::now();
	int ***map;
	map = new int **[18];
	for (size_t i = 0; i < 18; i++)
		map[i] = new int *[18];
	for (size_t i = 0; i < 18; i++)
	{
		map[i] = new int *[GRID_SIZE];
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			map[i][j] = new int[145];
		}
	}
	const double noiseScale = 0.05;
	for (int k = 0; k < 145; ++k)
	{
		double zCoord = k * noiseScale;
		for (int i = 0; i < 16; ++i)
		{
			double xCoord = ((_startPoint.x - 1) * 16 + i) * noiseScale;
			for (int j = 0; j < 16; ++j)
			{
				double yCoord = ((_startPoint.y - 1) * 16 + j) * noiseScale;
				map[i][j][k] = PGA::calcPerlin(xCoord, yCoord, zCoord);
			}
		}
	}
	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	std::cout << "Cavegen Time taken: " << duration << " milliseconds" << std::endl;
	return map;
}

void Chunk::PrintVoxelInfo()
{
	Voxel _voxel;
	printf("Chunk (%d)-(%d):\n", (int)_startPoint.x, (int)_startPoint.y);
	for (size_t x = 0; x < _length; x++)
	{
		for (size_t y = 0; y < _length; y++)
		{
			_voxel = GetVoxelByLocalCoordinate(x, y);
			printf("\tVoxel Local Pos: X:%ld, Y:%ld - Voxel Global Pos: (%d)-(%d)-(%d)\n",
				   x, y, (int)_voxel.Get_pos().x, (int)_voxel.Get_pos().y, (int)_voxel.Get_pos().z);
			printf("\t\t\tFaces UP:%d - DOWN:%d - North:%d - South:%d - West:%d - East:%d\n\t\tCaves:\n",
				   _voxel.IsUp(), _voxel.IsDown(), _voxel.IsNorth(), _voxel.IsSouth(), _voxel.IsWest(), _voxel.IsEast());

			_CAVE_LIST _caves = _voxel.GetCaves();
			for (auto cave : _caves)
			{
				printf("\t\t\tMin(%d) : Faces UP:%d - DOWN:%d - North:%d - South:%d - West:%d - East:%d\n",
					   cave.min.z, cave.min.face.IsUp(), cave.min.face.IsDown(), cave.min.face.IsNorth(),
					   cave.min.face.IsSouth(), cave.min.face.IsWest(), cave.min.face.IsEast());
				printf("\t\t\tmax(%d) : Faces UP:%d - DOWN:%d - North:%d - South:%d - West:%d - East:%d\n",
					   cave.max.z, cave.max.face.IsUp(), cave.max.face.IsDown(), cave.max.face.IsNorth(),
					   cave.max.face.IsSouth(), cave.max.face.IsWest(), cave.max.face.IsEast());
				printf("\t\t\t-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
			}
			printf("\n");
		}
	}
}