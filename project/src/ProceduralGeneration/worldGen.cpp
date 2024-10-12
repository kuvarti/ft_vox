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
															 PGA::calcPerlin(start.Get_x() + x, start.Get_y() + y)));
		}
	}
}

CaveGen::CaveGen(Vector2D s) : WorldGen(s.Get_x(), s.Get_y())
{
}

void CaveGen::Generate(Vector2D start)
{
	Vector2D v = WorldGen::GetLength();
	int column[145];

	const double noiseScale = 0.05;
	for (size_t i = 0; i < 16; ++i)
	{
		for (size_t j = 0; j < 16; ++j)
		{
			double xCoord = ((start.Get_x() - 1) * 16 + i) * noiseScale;
			double yCoord = ((start.Get_y() - 1) * 16 + j) * noiseScale;
			for (size_t k = 1; k <= 145; ++k)
			{
				double zCoord = k * noiseScale;
				column[k - 1] = PGA::calcPerlin(xCoord, yCoord, zCoord);
			}
			SeperateCaves(column, Vector2D(i, j));
			for (size_t k = 0; k < 145; k++)
				column[k] = 0;
		}
	}
}

void CaveGen::SeperateCaves(int *arr, Vector2D vox)
{
	size_t i;
	int start = 0;
	bool wall = false;
	for (i = 0; i < 145; i++)
	{
		if (arr[i] == 1 && wall == false)
		{
			start = i;
			wall = true;
			continue;
		}
		if (wall == true && arr[i] == 0)
		{
			GetVoxelByLocalCoordinate(vox).AddCave(start, i - 1);
			wall = false;
			start = 0;
		}
	}
	if (wall == true && start != 0)
		GetVoxelByLocalCoordinate(vox).AddCave(start, i - 1);
}