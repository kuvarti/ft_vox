#pragma once

#include "WorldGen.hpp"

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
	int ***_GenerateCave(); // todo this gonna be private

	_CAVE_LIST GetCaves() { return GetCaves(); }
	void PrintVoxelInfo();

protected:
	void Generate(glm::vec2 v) override
	{
		TerrainGen::Generate(v);
		CaveGen::Generate(v);
		// PrintVoxelInfo();
	}

private:
	glm::vec2 _startPoint;
	int _length;
};