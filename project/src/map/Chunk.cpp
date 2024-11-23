#include "Chunk.hpp"
#include "Settings.hpp"
#include "ProceduralGenerationAlgorithms.hpp"
#include "iostream"
#include <chrono>
#include <tuple>

Chunk::Chunk() : TerrainGen(glm::vec2(env->setting.ChunkSize, env->setting.ChunkSize)),
				 CaveGen(glm::vec2(env->setting.ChunkSize, env->setting.ChunkSize)),
				 WorldGen(env->setting.ChunkSize, env->setting.ChunkSize)
{
	_startPoint.x = 0;
	_startPoint.y = 0;
	_length = env->setting.ChunkSize;

	std::cout << "Chunk::Chunk() Called" << std::endl;
}

Chunk::Chunk(glm::vec2 startPoint) : TerrainGen(glm::vec2(env->setting.ChunkSize, env->setting.ChunkSize)),
									 CaveGen(glm::vec2(env->setting.ChunkSize, env->setting.ChunkSize)),
									 WorldGen(env->setting.ChunkSize, env->setting.ChunkSize)
{
	_startPoint = startPoint;
	_length = env->setting.ChunkSize;

	this->Generate(_startPoint);
}

Chunk::Chunk(float x, float y) : TerrainGen(glm::vec2(env->setting.ChunkSize, env->setting.ChunkSize)),
								 CaveGen(glm::vec2(env->setting.ChunkSize, env->setting.ChunkSize)),
								 WorldGen(env->setting.ChunkSize, env->setting.ChunkSize)
{
	_startPoint.x = x;
	_startPoint.y = y;
	_length = env->setting.ChunkSize;

	this->Generate(_startPoint);
}

Chunk::~Chunk()
{
	_vertices.clear();
	_indices.clear();
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

#define C_UINT16(A) (u_int16_t)(A)

void Chunk::InitIdices()
{
	_vertices.clear();
	_indices.clear();
	int vertexIndex = 0;

	for (size_t x = 0; x < _length; x++)
	{
		for (size_t y = 0; y < _length; y++)
		{
			Voxel voxel = GetVoxelByLocalCoordinate(x, y);
			std::vector<glm::vec3> cubeVertices;

			glm::vec3 vPos = voxel.Get_pos();
			if (voxel.IsUp())
			{
				cubeVertices.emplace_back(vPos + glm::vec3(-env->setting.halfCubeSize, -env->setting.halfCubeSize, env->setting.halfCubeSize)); // 4: kuzey, bati, ust
				cubeVertices.emplace_back(vPos + glm::vec3(env->setting.halfCubeSize, -env->setting.halfCubeSize, env->setting.halfCubeSize));	// 5: guney, bati, ust
				cubeVertices.emplace_back(vPos + glm::vec3(env->setting.halfCubeSize, env->setting.halfCubeSize, env->setting.halfCubeSize));	// 6: guney, dogu, ust
				cubeVertices.emplace_back(vPos + glm::vec3(-env->setting.halfCubeSize, env->setting.halfCubeSize, env->setting.halfCubeSize));	// 7: kuzey, dogu, ust
			}
			if (voxel.IsDown())
			{
				cubeVertices.emplace_back(vPos + glm::vec3(-env->setting.halfCubeSize, -env->setting.halfCubeSize, -env->setting.halfCubeSize)); // 0: kuzey, bati, alt
				cubeVertices.emplace_back(vPos + glm::vec3(env->setting.halfCubeSize, -env->setting.halfCubeSize, -env->setting.halfCubeSize));	 // 1: guney, bati, alt
				cubeVertices.emplace_back(vPos + glm::vec3(env->setting.halfCubeSize, env->setting.halfCubeSize, -env->setting.halfCubeSize));	 // 2: guney, dogu, alt
				cubeVertices.emplace_back(vPos + glm::vec3(-env->setting.halfCubeSize, env->setting.halfCubeSize, -env->setting.halfCubeSize));	 // 3: kuzey, dogu, alt
			}
			if (voxel.IsNorth())
			{
				if (voxel.IsUp())
				{
					cubeVertices.emplace_back(vPos + glm::vec3(-env->setting.halfCubeSize, -env->setting.halfCubeSize, -env->setting.halfCubeSize)); // 0: kuzey, bati, alt
					cubeVertices.emplace_back(vPos + glm::vec3(-env->setting.halfCubeSize, env->setting.halfCubeSize, -env->setting.halfCubeSize));	 // 3: kuzey, dogu, alt
				}
				if (voxel.IsDown())
				{
					cubeVertices.emplace_back(vPos + glm::vec3(-env->setting.halfCubeSize, -env->setting.halfCubeSize, env->setting.halfCubeSize)); // 4: kuzey, bati, ust
					cubeVertices.emplace_back(vPos + glm::vec3(-env->setting.halfCubeSize, env->setting.halfCubeSize, env->setting.halfCubeSize));	// 7: kuzey, dogu, ust
				}
			}
			if (voxel.IsSouth())
			{
				if (voxel.IsUp())
				{
					cubeVertices.emplace_back(vPos + glm::vec3(env->setting.halfCubeSize, -env->setting.halfCubeSize, -env->setting.halfCubeSize)); // 1: guney, bati, alt
					cubeVertices.emplace_back(vPos + glm::vec3(env->setting.halfCubeSize, env->setting.halfCubeSize, -env->setting.halfCubeSize));	// 2: guney, dogu, alt
				}
				if (voxel.IsDown())
				{
					cubeVertices.emplace_back(vPos + glm::vec3(env->setting.halfCubeSize, -env->setting.halfCubeSize, env->setting.halfCubeSize)); // 5: guney, bati, ust
					cubeVertices.emplace_back(vPos + glm::vec3(env->setting.halfCubeSize, env->setting.halfCubeSize, env->setting.halfCubeSize));  // 6: guney, dogu, ust
				}
			}
			if (voxel.IsWest())
			{
				if (voxel.IsUp())
				{
					cubeVertices.emplace_back(vPos + glm::vec3(-env->setting.halfCubeSize, -env->setting.halfCubeSize, -env->setting.halfCubeSize)); // 0: kuzey, bati, alt
					cubeVertices.emplace_back(vPos + glm::vec3(env->setting.halfCubeSize, -env->setting.halfCubeSize, -env->setting.halfCubeSize));	 // 1: guney, bati, alt
				}
				if (voxel.IsDown())
				{
					cubeVertices.emplace_back(vPos + glm::vec3(-env->setting.halfCubeSize, -env->setting.halfCubeSize, env->setting.halfCubeSize)); // 4: kuzey, bati, ust
					cubeVertices.emplace_back(vPos + glm::vec3(env->setting.halfCubeSize, -env->setting.halfCubeSize, env->setting.halfCubeSize));	// 5: guney, bati, ust
				}
			}
			if (voxel.IsEast())
			{
				if (voxel.IsUp())
				{
					cubeVertices.emplace_back(vPos + glm::vec3(env->setting.halfCubeSize, env->setting.halfCubeSize, -env->setting.halfCubeSize));	// 2: guney, dogu, alt
					cubeVertices.emplace_back(vPos + glm::vec3(-env->setting.halfCubeSize, env->setting.halfCubeSize, -env->setting.halfCubeSize)); // 3: kuzey, dogu, alt
				}
				if (voxel.IsDown())
				{
					cubeVertices.emplace_back(vPos + glm::vec3(env->setting.halfCubeSize, env->setting.halfCubeSize, env->setting.halfCubeSize));  // 6: guney, dogu, ust
					cubeVertices.emplace_back(vPos + glm::vec3(-env->setting.halfCubeSize, env->setting.halfCubeSize, env->setting.halfCubeSize)); // 7: kuzey, dogu, ust
				}
			}
			_vertices.insert(_vertices.end(), cubeVertices.begin(), cubeVertices.end());

			std::vector<uint16_t> cubeIndices = {
				C_UINT16(vertexIndex), C_UINT16(vertexIndex + 1), C_UINT16(vertexIndex + 2),
				C_UINT16(vertexIndex), C_UINT16(vertexIndex + 2), C_UINT16(vertexIndex + 3), // Arka yüz
				C_UINT16(vertexIndex + 4), C_UINT16(vertexIndex + 5), C_UINT16(vertexIndex + 6),
				C_UINT16(vertexIndex + 4), C_UINT16(vertexIndex + 6), C_UINT16(vertexIndex + 7), // Ön yüz
				C_UINT16(vertexIndex + 3), C_UINT16(vertexIndex + 2), C_UINT16(vertexIndex + 6),
				C_UINT16(vertexIndex + 3), C_UINT16(vertexIndex + 6), C_UINT16(vertexIndex + 7), // Üst yüz
				C_UINT16(vertexIndex), C_UINT16(vertexIndex + 1), C_UINT16(vertexIndex + 5),
				C_UINT16(vertexIndex), C_UINT16(vertexIndex + 5), C_UINT16(vertexIndex + 4), // Alt yüz
				C_UINT16(vertexIndex + 1), C_UINT16(vertexIndex + 2), C_UINT16(vertexIndex + 6),
				C_UINT16(vertexIndex + 1), C_UINT16(vertexIndex + 6), C_UINT16(vertexIndex + 5), // Sağ yüz
				C_UINT16(vertexIndex + 0), C_UINT16(vertexIndex + 3), C_UINT16(vertexIndex + 7),
				C_UINT16(vertexIndex + 0), C_UINT16(vertexIndex + 7), C_UINT16(vertexIndex + 4) // Sol yüz
			};
			_indices.insert(_indices.end(), cubeIndices.begin(), cubeIndices.end());
			vertexIndex += 8;
		}
	}
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