#include "WorldGen.hpp"
#include "ProceduralGenerationAlgorithms.hpp"
/* ====== TerrainGeneration ====== */

TerrainGen::TerrainGen(glm::vec2 s) : WorldGen(s.x, s.y)
{
}

void TerrainGen::Generate(glm::vec2 start)
{
	int z = 0;
	glm::vec2 l = WorldGen::GetLength();
	for (size_t x = 0; x < l.x; x++)
	{
		for (size_t y = 0; y < l.y; y++)
		{
			Voxel &v = GetVoxelByLocalCoordinate(x, y);
			v.Set_2dPos(start.x + x, start.y + y);
			z = v.Get_pos().z;
			if (z == 0)
			{
				z = v.Set_z(PGA::calcPerlin(start.x + x, start.y + y));
			}

			v.SetFace(VOXEL_FACE_UP);
			if (x == 0)
			{
				if (PGA::calcPerlin(start.x - 1, start.y + y) < z)
					v.SetFace(VOXEL_FACE_NORTH);
			}

			if (x == l.x - 1)
			{
				if (PGA::calcPerlin(start.x + l.x, start.y + y) < z)
					v.SetFace(VOXEL_FACE_SOUTH);
			}
			else
			{
				Voxel &Vnext = GetVoxelByLocalCoordinate(x + 1, y);
				if (Vnext.Set_z(PGA::calcPerlin(start.x + x + 1, start.y + y)) < z)
					v.SetFace(VOXEL_FACE_SOUTH);
				else if (Vnext.Get_pos().z > z)
					Vnext.SetFace(VOXEL_FACE_NORTH);
			}

			if (y == 0)
			{
				if (PGA::calcPerlin(start.x + x, start.y - 1) < z)
					v.SetFace(VOXEL_FACE_WEST);
			}

			if (y == l.y - 1)
			{
				if (PGA::calcPerlin(start.x + x, start.y + l.y) < z)
					v.SetFace(VOXEL_FACE_EAST);
			}
			else
			{
				Voxel &Vnext = GetVoxelByLocalCoordinate(x, y + 1);
				if (Vnext.Set_z(PGA::calcPerlin(start.x + x, start.y + y + 1)) < z)
					v.SetFace(VOXEL_FACE_EAST);
				else if (z < Vnext.Get_pos().z)
					Vnext.SetFace(VOXEL_FACE_WEST);
			}
		}
	}
}

/* ====== CaveGeneration ====== */

CaveGen::CaveGen(glm::vec2 s) : WorldGen(s.x, s.y)
{
}

void CaveGen::Generate(glm::vec2 start)
{
	glm::vec2 l = WorldGen::GetLength();
	_CAVE_LIST nextcaves;
	int *column = new int[145], *columnNext = new int[145];

	const double noiseScale = 0.05;
	for (size_t x = 0; x < l.x; ++x)
	{
		for (size_t y = 0; y < l.y; ++y)
		{
			double xCoord = ((start.x - 1) * l.x + x) * noiseScale;
			double yCoord = ((start.y - 1) * l.y + y) * noiseScale;
			_CAVE_LIST &caves = GetVoxelByLocalCoordinate(x, y).GetAndChangeCaves();
			if (caves.empty())
			{
				Voxel &v = GetVoxelByLocalCoordinate(x, y);
				column = GetColumns(xCoord, yCoord, noiseScale);
				caves = SeperateCaves(column, v.Get_pos().z);
			}

			// if (x == 0)
			// {
			// 	xCoord = ((start.x - 1) * 16 + x - 1) * noiseScale;
			// 	columnNext = GetColumns(xCoord, yCoord, noiseScale);
			// 	SetFaces(caves, columnNext, VOXEL_FACE_WEST);
			// 	delete[] columnNext;
			// }
			// if (x == l.x - 1)
			// {
			// 	xCoord = ((start.x - 1) * 16 + x + l.x) * noiseScale;
			// 	columnNext = GetColumns(xCoord, yCoord, noiseScale);
			// 	SetFaces(caves, columnNext, VOXEL_FACE_EAST);
			// 	delete[] columnNext;
			// }
			// else
			// {
			// 	Voxel &Vnext = GetVoxelByLocalCoordinate(x + 1, y);
			// 	xCoord = ((start.x - 1) * l.x + x + 1) * noiseScale;
			// 	columnNext = GetColumns(xCoord, yCoord, noiseScale);
			// 	nextcaves = SeperateCaves(columnNext, Vnext.z);
			// 	SetFaces(caves, nextcaves, VOXEL_FACE_EAST, VOXEL_FACE_WEST);
			// 	for (auto &l : nextcaves)
			// 	{
			// 		Vnext.AddCave(l.min, l.max);
			// 	}
			// 	delete[] columnNext;
			// 	nextcaves.clear();
			// }
			// if (y == 0)
			// {
			// 	yCoord = ((start.y - 1) * l.y + y - 1) * noiseScale;
			// 	columnNext = GetColumns(xCoord, yCoord, noiseScale);
			// 	SetFaces(caves, columnNext, VOXEL_FACE_NORTH);
			// 	delete[] columnNext;
			// }
			// if (y == l.y - 1)
			// {
			// 	yCoord = ((start.y - 1) * l.y + y + l.y) * noiseScale;
			// 	columnNext = GetColumns(xCoord, yCoord, noiseScale);
			// 	SetFaces(caves, columnNext, VOXEL_FACE_SOUTH);
			// 	delete[] columnNext;
			// }
			// else
			// {
			// 	Voxel &Vnext = GetVoxelByLocalCoordinate(x, y + 1);
			// 	yCoord = ((start.y - 1) * l.y + y + 1) * noiseScale;
			// 	columnNext = GetColumns(xCoord, yCoord, noiseScale);
			// 	nextcaves = SeperateCaves(columnNext, Vnext.z);
			// 	SetFaces(caves, nextcaves, VOXEL_FACE_SOUTH, VOXEL_FACE_NORTH);
			// 	for (auto &l : nextcaves)
			// 	{
			// 		Vnext.AddCave(l.min, l.max);
			// 	}
			// 	delete[] columnNext;
			// 	nextcaves.clear();
			// }
		}
	}
	delete[] column;
}

void CaveGen::SetFaces(_CAVE_LIST &list, _CAVE_LIST &next, unsigned char listFlag, unsigned char nextFlag)
{
	for (_CAVE_LIST::iterator itl = list.begin(), itc = next.begin(); itl != list.end(); itl++)
	{
		while (itc != next.end() && (*itl).min.z >= (*itc).max.z)
		{
			itc++;
		}
		if ((*itl).min.z < (*itc).min.z)
			(*itc).min.face.SetFace(nextFlag);
		else if ((*itl).min.z > (*itc).min.z)
			(*itl).min.face.SetFace(listFlag);
		if ((*itl).max.z < (*itc).max.z)
			(*itl).max.face.SetFace(listFlag);
		else if ((*itl).max.z > (*itc).max.z)
			(*itc).max.face.SetFace(nextFlag);
	}
}

void CaveGen::SetFaces(_CAVE_LIST &list, int *next, unsigned char flag)
{
	for (_CAVE_LIST::iterator it = list.begin(); it != list.end(); it++)
	{
		if (next[(*it).min.z] == 0)
			(*it).min.face.SetFace(flag);
		if (next[(*it).max.z] == 0)
			(*it).max.face.SetFace(flag);
	}
}

int *CaveGen::GetColumns(double x, double y, double noiseScale)
{
	int *column = new int[145];
	size_t tmp;

	for (size_t i = 0; i < 145; i++)
		column[i] = 0;
	for (size_t k = 0; k < 145; k += 5)
	{
		double zCoord = (k + 1) * noiseScale;
		column[k] = PGA::calcPerlin(x, y, zCoord);
		if (column[k] == 1) {
			tmp = k;
			do {
				if (tmp == 0)
					break;
				tmp--;
				zCoord = (tmp + 1) * noiseScale;
				column[tmp] = PGA::calcPerlin(x, y, zCoord);
			} while (column[tmp] == 1 && column[tmp - 1] == 0);
		}
	}
	return column;
}

std::list<Cave> CaveGen::SeperateCaves(int *arr, size_t _max)
{
	size_t i;
	_CAVE_LIST cave;
	CaveWall min(0), max(0);
	bool wall = false;
	for (i = 0; i < 145; i++)
	{
		if (arr[i] == 1 && wall == false)
		{
			min = CaveWall(i);
			min.face.SetFace(VOXEL_FACE_UP);
			wall = true;
			continue;
		}
		if (wall == true && (arr[i] == 0 || i == _max))
		{
			max = CaveWall(i - 1);
			max.face.SetFace(VOXEL_FACE_DOWN);
			cave.emplace_back(min, max);
			wall = false;
		}
		if (i == _max)
			return cave;
	}
	if (wall == true)
	{
		max = CaveWall(i - 1);
		max.face.SetFace(VOXEL_FACE_DOWN);
		cave.emplace_back(min, max);
	}
	return cave;
}