#include "worldGen.hpp"
#include "ProceduralGenerationAlgorithms.hpp"
/* ====== TerrainGeneration ====== */

TerrainGen::TerrainGen(Vector2D s) : WorldGen(s.Get_x(), s.Get_y())
{
}

void TerrainGen::Generate(Vector2D start)
{
	Vector2D v = WorldGen::GetLength();
	for (size_t x = 0; x < v.Get_x(); x++)
	{
		for (size_t y = 0; y < v.Get_y(); y++)
		{
			SetVoxelByLocalCoordinaate(Vector2D(x, y), Voxel(start.Get_x() + x, start.Get_y() + y,
															 calcPerlin(start.Get_x() + x, start.Get_y() + y)));
		}
	}
}

CaveGen::CaveGen(Vector2D s) : WorldGen(s.Get_x(), s.Get_y())
{
}

void CaveGen::Generate(Vector2D start)
{
}