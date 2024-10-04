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
	for (size_t i = x; i < x + 8; i++)
	{
		for (size_t j = y; j < y + 8; j++)
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

// Uint32 *newRender(int x) {
// 	Uint32* pixels = new Uint32[800 * 800];
// 	int **map1 = cellular(x, 16);
// 	int **map2;
// 	for (size_t i = 0, px = 100; i < 16; i++, px += 8)
// 	{
// 		map2 = cellular((int)i, 16);
// 		for (size_t y = 0, py = 0; y < 70; y++, py += 8)
// 		{
// 			if (map1[x][y] == 1 && map2[x][y] == 1)
// 				fill4x4(pixels, py, px, 255);
// 			else
// 				fill4x4(pixels, py, px, 0);
// 		}
// 		mapfree(map2);
// 	}
// 	mapfree(map1);
// 	return pixels;
// }

Uint32 *newRender(int x)
{
	Uint32 *pixels = new Uint32[800 * 800];
	Chunk a(320, 320);
	int ***map = a._GenerateCave();
	x++;
	for (size_t y = 1, px = 100; y <= 16; y++, px += 8)
	{
		for (size_t z = 0, py = 10; z < 70; z++, py += 8)
		{
			fill4x4(pixels, py, px, map[x][y][z] == 1 ? 255 : 0);
		}
	}
	for (int i = 17; i >= 0; i--)
	{
		for (int j = 17; j >= 0; j--)
		{
			delete[] map[i][j];
		}
		delete[] map[i];
	}
	delete[] map;
	return pixels;
}