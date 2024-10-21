#include "chunk.hpp"
#include "global.hpp"
#include <unordered_map>
#include <chrono>

void deneme()
{
	const int start = -8192;
	const int end = 8192;
	const int step = 16;

	auto startTime = std::chrono::high_resolution_clock::now();
	std::unordered_map<std::tuple<int, int>, Chunk *> Chunks;

	bool overlapFound = false;
	for (int x = start; x <= end; x += step)
	{
		for (int y = start; y <= end; y += step)
		{
			auto currentCoord = std::make_tuple(x, y);
			if (Chunks.find(currentCoord) != Chunks.end())
			{
				std::cout << "Overlap found at (" << x << ", " << y << ")" << std::endl;
				overlapFound = true;
				break;
			}
			else
			{
				// Chunks.insert_or_assign(std::make_tuple(x/16, y/16), new Chunk(x, y));
			}
			std::cout << "Chunk at (" << x / 16 + x % 16 << ", " << y / 16 + y % 16 << ") (" << x << ", " << y << ") Created" << std::endl;
		}
	}
	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	std::cout << "Total number of chunks: " << Chunks.size() << std::endl;
	std::cout << "Time taken: " << duration << " milliseconds" << std::endl;
}

void fill4x4(Uint32 *a, int x, int y, int color)
{
	for (size_t i = x; i < x + 4; i++)
	{
		for (size_t j = y; j < y + 4; j++)
		{
			a[i * 800 + j] = (color << 24) | (color << 16) | (color << 8) | color;
		}
	}
}

void fillRectWith4x4(Uint32 *a, int x, int y, int w, int h, int color)
{
	for (size_t i = x; i < x + w; i++)
	{
		for (size_t j = y; j < y + h; j++)
		{
			a[i * 800 + j] = (color << 24) | (color << 16) | (color << 8) | color;
		}
	}
}

void mapfree(int **m)
{
	for (size_t i = 0; i < 16; i++)
	{
		delete[] m[i];
	}
	delete[] m;
}

Uint32 *newRender(int x)
{
	Uint32 *pixels = new Uint32[800 * 800];
	size_t px = 10;
	for (size_t i = 0; i < 800 * 800; i++)
	{
		pixels[i] = 0;
	}
	Chunk a(304, 304);
	// Chunk b(320, 320);
	// Chunk c(336, 336), d(352, 352);
	x++;
	for (size_t y = 1; y <= 32; y++, px += 4)
	{
		if (y <= 16)
		{
			Voxel &v = a.GetVoxelByLocalCoordinate(x, y - 1);
			_CAVE_LIST cave = v.GetCaves();
			for (auto &l : cave)
			{
				fillRectWith4x4(pixels, l.min.z * 4, px, (l.max.z - l.min.z) * 4, 4, 255);
			}
		}
		else
		{
			// Voxel& v = b.GetVoxelByLocalCoordinate(x, y - 17);
			// _CAVE_LIST cave = v.getCaves();
			// for(auto& l : cave) {
			// 	fillRectWith4x4(pixels, l.min.z * 4, px, (l.max.z - l.min.z) * 4, 4, 255);
			// }
		}
	}
	// for (size_t y = 1; y <= 32; y++, px += 4)
	// {
	// 	if (y <= 16){
	// 		Voxel& v = c.GetVoxelByLocalCoordinate(x, y - 1);
	// 		_CAVE_LIST cave = v.getCaves();
	// 		for(auto& l : cave) {
	// 			fillRectWith4x4(pixels, l.min.z * 4, px, (l.max.z - l.min.z) * 4, 4, 255);
	// 		}
	// 	}
	// 	else {
	// 		Voxel& v = d.GetVoxelByLocalCoordinate(x, y - 17);
	// 		_CAVE_LIST cave = v.getCaves();
	// 		for(auto& l : cave) {
	// 			fillRectWith4x4(pixels, l.min.z * 4, px, (l.max.z - l.min.z) * 4, 4, 255);
	// 		}
	// 	}
	// }
	return pixels;
}