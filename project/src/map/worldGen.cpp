#include "worldGen.hpp"
#include "ProceduralGenerationAlgorithms.hpp"
/* ====== TerrainGeneration ====== */

TerrainGen::TerrainGen(Vector2D s) : WorldGen(s.Get_x(), s.Get_y())
{
}

void TerrainGen::Generate(Vector2D start)
{
	int z = 0;
	Vector2D l = WorldGen::GetLength();
	for (size_t x = 0; x < l.Get_x(); x++)
	{
		for (size_t y = 0; y < l.Get_y(); y++)
		{
			Voxel& v = GetVoxelByLocalCoordinate(x, y);
			v.Set_2dPos(start.Get_x() + x, start.Get_y() + y);
			z = v.Get_z();
			if (z == 0) {
				z = v.Set_z(PGA::calcPerlin(start.Get_x() + x, start.Get_y() + y));
			}

			v.SetFace(VOXEL_FACE_UP);
			if (x == 0) {
				if (PGA::calcPerlin(start.Get_x() - 1, start.Get_y() + y) < z)
					v.SetFace(VOXEL_FACE_WEST);
			}

			if (x == l.Get_x() - 1) {
				if (PGA::calcPerlin(start.Get_x() + l.Get_x(), start.Get_y() + y) < z)
					v.SetFace(VOXEL_FACE_EAST);
			}
			else {
				Voxel& Vnext = GetVoxelByLocalCoordinate(x + 1, y);
				if (Vnext.Set_z(PGA::calcPerlin(start.Get_x() + x + 1, start.Get_y() + y)) < z)
					v.SetFace(VOXEL_FACE_EAST);
				else if (Vnext.Get_z() > z)
					Vnext.SetFace(VOXEL_FACE_WEST);
			}

			if (y == 0) {
				if (PGA::calcPerlin(start.Get_x() + x, start.Get_y() - 1) < z)
					v.SetFace(VOXEL_FACE_NORTH);
			}

			if (y == l.Get_y() - 1) {
				if (PGA::calcPerlin(start.Get_x() + x, start.Get_y() + l.Get_y()) < z)
					v.SetFace(VOXEL_FACE_SOUTH);
			}
			else {
				Voxel& Vnext = GetVoxelByLocalCoordinate(x, y + 1);
				if (Vnext.Set_z(PGA::calcPerlin(start.Get_x() + x, start.Get_y() + y + 1)) < z)
					v.SetFace(VOXEL_FACE_SOUTH);
				else if (Vnext.Get_z() > z)
					Vnext.SetFace(VOXEL_FACE_NORTH);
			}
		}
	}
}

void TerrainGen::SetFaces() {
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

void CaveGen::SetFaces() {
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