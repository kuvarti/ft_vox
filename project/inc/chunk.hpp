#pragma once

#include "worldGen.hpp"

#define GRID_SIZE 128
#define CHUNK_SIZE 16

class Chunk : public TerrainGen, public CaveGen
{
public:
	Chunk();
	Chunk(Vector2D);
	Chunk(float, float);
	~Chunk();

	void ChangeStartPosition(Vector2D);
	Voxel	GetVoxelbyGlobalCoordinate(Vector2D) const;
	Voxel	GetVoxelbyGlobalCoordinate(int, int) const;
	int ***_GenerateCave(); // todo this gonna be private

	void PrintVoxelInfo();

protected:
	void Generate(Vector2D v) override
	{
		TerrainGen::Generate(v);
		// CaveGen::Generate(v);
		PrintVoxelInfo();
	}
	void SetFaces() override {}

private:
	Vector2D _startPoint;
	int _length;
};