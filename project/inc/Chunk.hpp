#pragma once

#include "WorldGen.hpp"
#include <vector>

class Chunk : public TerrainGen, public CaveGen
{
public:
	Chunk();
	Chunk(glm::vec2);
	Chunk(float, float);
	~Chunk();

	void ChangeStartPosition(glm::vec2);
	Voxel GetVoxelbyGlobalCoordinate(glm::vec2) const;
	Voxel GetVoxelbyGlobalCoordinate(int, int) const;

	const std::vector<glm::vec3>getVertices() const{
		return _vertices;
	};
	const std::vector<uint16_t>& getIndices() const{
		return _indices;
	};

	_CAVE_LIST GetCaves() { return GetCaves(); }
	void PrintVoxelInfo();

protected:
	void Generate(glm::vec2 v) override
	{
		TerrainGen::Generate(v);
		CaveGen::Generate(v);
		this->InitIdices();
	}

private:
	void	InitIdices();

	std::vector<uint16_t>	_indices;
	std::vector<glm::vec3>	_vertices;
	glm::vec2				_startPoint;
	int _length;
};