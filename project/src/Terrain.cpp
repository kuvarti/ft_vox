#include "Terrain.hpp"
#include "chunk.hpp"
#include <iostream>
#include <chrono>

Terrain::Terrain()
{
	const int gridSize = 16;
	const float cubeSize = 1.0f;
	const float halfCubeSize = cubeSize / 2.0f;

	for (int x = 0; x < gridSize; ++x)
	{
		for (int y = -50; y < 0; ++y)
		{
			for (int z = 0; z < gridSize; ++z)
			{
				float xPos = x * cubeSize;
				float yPos = y * cubeSize;
				float zPos = z * cubeSize;

				vertices.push_back(Vertex{glm::vec3(xPos - halfCubeSize, yPos - halfCubeSize, zPos - halfCubeSize)});
				vertices.push_back(Vertex{glm::vec3(xPos + halfCubeSize, yPos - halfCubeSize, zPos - halfCubeSize)});
				vertices.push_back(Vertex{glm::vec3(xPos + halfCubeSize, yPos - halfCubeSize, zPos + halfCubeSize)});
				vertices.push_back(Vertex{glm::vec3(xPos - halfCubeSize, yPos - halfCubeSize, zPos + halfCubeSize)});
				vertices.push_back(Vertex{glm::vec3(xPos - halfCubeSize, yPos + halfCubeSize, zPos - halfCubeSize)});
				vertices.push_back(Vertex{glm::vec3(xPos + halfCubeSize, yPos + halfCubeSize, zPos - halfCubeSize)});
				vertices.push_back(Vertex{glm::vec3(xPos + halfCubeSize, yPos + halfCubeSize, zPos + halfCubeSize)});
				vertices.push_back(Vertex{glm::vec3(xPos - halfCubeSize, yPos + halfCubeSize, zPos + halfCubeSize)});

				uint16_t startIndex = static_cast<uint16_t>(vertices.size() - 8);
				indices.push_back(startIndex);
				indices.push_back(startIndex + 1);
				indices.push_back(startIndex + 2);
				indices.push_back(startIndex);
				indices.push_back(startIndex + 2);
				indices.push_back(startIndex + 3);

				indices.push_back(startIndex + 4);
				indices.push_back(startIndex + 5);
				indices.push_back(startIndex + 6);
				indices.push_back(startIndex + 4);
				indices.push_back(startIndex + 6);
				indices.push_back(startIndex + 7);

				indices.push_back(startIndex);
				indices.push_back(startIndex + 1);
				indices.push_back(startIndex + 5);
				indices.push_back(startIndex);
				indices.push_back(startIndex + 5);
				indices.push_back(startIndex + 4);

				indices.push_back(startIndex + 1);
				indices.push_back(startIndex + 2);
				indices.push_back(startIndex + 6);
				indices.push_back(startIndex + 1);
				indices.push_back(startIndex + 6);
				indices.push_back(startIndex + 5);

				indices.push_back(startIndex + 2);
				indices.push_back(startIndex + 3);
				indices.push_back(startIndex + 7);
				indices.push_back(startIndex + 2);
				indices.push_back(startIndex + 7);
				indices.push_back(startIndex + 6);

				indices.push_back(startIndex + 3);
				indices.push_back(startIndex);
				indices.push_back(startIndex + 4);
				indices.push_back(startIndex + 3);
				indices.push_back(startIndex + 4);
				indices.push_back(startIndex + 7);
			}
		}
	}
}

const std::vector<Terrain::Vertex> &Terrain::getVertices() const
{
	return vertices;
}

const std::vector<uint16_t> &Terrain::getIndices() const
{
	return indices;
}

Terrain1::Terrain1()
{
	printf("WARN: Terrain class has no pivot location.\n\t\tMap is not generated.");
}

Terrain1::Terrain1(glm::vec2 camera)
{
	_InitMap(camera);
}

Terrain1::~Terrain1()
{
	printf("ChunkList Size: %d\n", _chunk_list.size());
	auto it = _chunk_list.begin();
	while (it != _chunk_list.end())
	{
		delete it->second;
		it = _chunk_list.erase(it); // erase() returns the next valid iterator
	}
}

const Chunk *Terrain1::GetChunkByGlobalPos(glm::vec2 pos) const
{
	auto ret = _chunk_list.find(glm::vec2((int)(pos.x / 16) * 16, (int)(pos.y / 16) * 16));
	if (ret != _chunk_list.end())
	{
		return ret->second;
	}
	return nullptr;
}

bool Terrain1::UpdateMap(glm::vec2 camera)
{
	if (_IsPivotMoved(camera))
	{
		glm::vec2 oldPivot(_pivot);
		camera.x = (int)(camera.x / 16);
		camera.y = (int)(camera.y / 16);
		_pivot = camera;

		for (int y = -CALC_RANGE; y <= CALC_RANGE; y++)
		{
			for (int x = -CALC_RANGE; x <= CALC_RANGE; x++)
			{
				if (x * x + y * y <= CALC_RANGE * CALC_RANGE)
				{
					int newX = _pivot.x + x;
					int newY = _pivot.y + y;
					int oldX = oldPivot.x + x;
					int oldY = oldPivot.y + y;
					if ((newX - oldPivot.x) * (newX - oldPivot.x) + (newY - oldPivot.y) * (newY - oldPivot.y) > CALC_RANGE * CALC_RANGE)
					{
						_AddChunk(newX, newY);
					}
				}
			}
		}
		for (int y = -CALC_RANGE; y <= CALC_RANGE; y++)
		{
			for (int x = -CALC_RANGE; x <= CALC_RANGE; x++)
			{
				if (x * x + y * y <= CALC_RANGE * CALC_RANGE)
				{
					int oldX = oldPivot.x + x;
					int oldY = oldPivot.y + y;
					int newX = _pivot.x + x;
					int newY = _pivot.y + y;
					if ((oldX - _pivot.x) * (oldX - _pivot.x) + (oldY - _pivot.y) * (oldY - _pivot.y) > CALC_RANGE * CALC_RANGE)
					{
						_RemoveChunk(oldX, oldY);
					}
				}
			}
		}
		return true;
	}
	return false;
}

bool Terrain1::UpdateMap(glm::vec3 camera)
{
	return UpdateMap(glm::vec2(camera.x, camera.y));
}

void Terrain1::_InitMap(glm::vec2 camera)
{
	camera.x = (int)(camera.x / 16);
	camera.y = (int)(camera.y / 16);

	_pivot = camera;
	for (int y = -CALC_RANGE; y <= CALC_RANGE; y++)
	{
		for (int x = -CALC_RANGE; x <= CALC_RANGE; x++)
		{
			if (x * x + y * y <= CALC_RANGE * CALC_RANGE)
			{
				_AddChunk(camera.x + x, camera.y + y);
			}
		}
	}
}

bool Terrain1::_IsPivotMoved(glm::vec2 c)
{
	if ((int)(_pivot.x) == (int)(c.x / 16) &&
		(int)(_pivot.y) == (int)(c.y / 16))
		return false;

	if ((c.x - 16 > _pivot.x + 2) ||
		(c.x + 16 < _pivot.x + CHUNK_SIZE + 2))
		return true;
	if ((c.y - 16 > _pivot.y + 2) ||
		(c.y + 16 < _pivot.y + CHUNK_SIZE + 2))
		return true;
	return false;
}

void Terrain1::_AddChunk(int x, int y)
{
	glm::vec2 pos(x, y);
	if (_chunk_list.find(pos) == _chunk_list.end())
	{
		_chunk_list.emplace(pos, new Chunk(/*glm::vec2(x, y)*/));
	}
}

void Terrain1::_RemoveChunk(int x, int y)
{
	glm::vec2 chunkPos(x, y);
	auto it = _chunk_list.find(chunkPos);
	if (it != _chunk_list.end())
	{
		delete it->second;
		_chunk_list.erase(it);
	}
}