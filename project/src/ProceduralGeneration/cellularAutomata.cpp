#include "chunk.hpp"
#include "unistd.h"

int randomVoxel(int iv, int iy) {
	const unsigned w = 8 * sizeof(unsigned);
	const unsigned s = w / 2; 
	unsigned a = iv, b = iy;
	a *= 3284157443;
	b ^= a << s | a >> w - s;
	b *= 1911520717;
	a ^= b << s | b >> w - s;
	a *= 2048419325;

	return (a < (0xffffffff * 0.35));
}

int GetSurroundingWallCount(int gridX, int gridY, int **map) {
	int wallCount = 0;
	for (int neighbourX = gridX - 1; neighbourX <= gridX + 1; neighbourX ++) {
		for (int neighbourY = gridY - 1; neighbourY <= gridY + 1; neighbourY ++) {
			if (neighbourX >= 0 && neighbourX < 16 && neighbourY >= 0 && neighbourY < 70) {
				if (neighbourX != gridX || neighbourY != gridY) {
					wallCount += map[neighbourX][neighbourY];
				}
			}
			else {
				wallCount ++;
			}
		}
	}
	return wallCount;
}

void SmoothMap(int **map) {
	for (int x = 0; x < 16; x ++) {
		for (int y = 0; y < 70; y ++) {
			int neighbourWallTiles = GetSurroundingWallCount(x,y,map);
			if (neighbourWallTiles > 4)
				map[x][y] = 1;
			else if (neighbourWallTiles < 4)
				map[x][y] = 0;
		}
	}
}

int **cellular(int xmi) {
	// 70: caves can be => 30 <-> 100
	int **map1;
	map1 = new int*[16];
	for (size_t i = 0; i < 16; i++)
		map1[i] = new int[70];

	for (size_t x = xmi; x < xmi+16; x++)
	{
		for (size_t y = 0; y < 70; y++)
		{
			map1[x - xmi][y] = randomVoxel(x, y + 30);
		}
	}
	SmoothMap(map1);
	return map1;
}