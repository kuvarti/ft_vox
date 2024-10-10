#include "ProceduralGenerationAlgorithms.hpp"
#include "chunk.hpp"

float PGA::perlinNoise2d(float x, float y)
{
	int x0 = (int)x;
	int y0 = (int)y;
	int x1 = x0 + 1;
	int y1 = y0 + 1;

	float sx = x - (float)x0;
	float sy = y - (float)y0;

	float n0 = dotGridGradient(x0, y0, x, y);
	float n1 = dotGridGradient(x1, y0, x, y);
	float ix0 = interpolate2d(n0, n1, sx);

	n0 = dotGridGradient(x0, y1, x, y);
	n1 = dotGridGradient(x1, y1, x, y);
	float ix1 = interpolate2d(n0, n1, sx);

	float value = interpolate2d(ix0, ix1, sy);
	return value;
}

float PGA::perlinNoise3d(float x, float y, float z) {
	int x0 = (int)x;
	int y0 = (int)y;
	int z0 = (int)z;
	int x1 = x0 + 1;
	int y1 = y0 + 1;
	int z1 = z0 + 1;

	float sx = x - (float)x0;
	float sy = y - (float)y0;
	float sz = z - (float)z0;

	float n0 = dotGridGradient(x0, y0, z0, x, y, z);
	float n1 = dotGridGradient(x1, y0, z0, x, y, z);
	float ix0 = interpolate3d(n0, n1, sx);

	n0 = dotGridGradient(x0, y1, z0, x, y, z);
	n1 = dotGridGradient(x1, y1, z0, x, y, z);
	float ix1 = interpolate3d(n0, n1, sx);

	float iy0 = interpolate3d(ix0, ix1, sy);

	n0 = dotGridGradient(x0, y0, z1, x, y, z);
	n1 = dotGridGradient(x1, y0, z1, x, y, z);
	ix0 = interpolate3d(n0, n1, sx);

	n0 = dotGridGradient(x0, y1, z1, x, y, z);
	n1 = dotGridGradient(x1, y1, z1, x, y, z);
	ix1 = interpolate3d(n0, n1, sx);

	float iy1 = interpolate3d(ix0, ix1, sy);

	float value = interpolate3d(iy0, iy1, sz);
	return value;
}


float mapRangeWithZero(float x, float x_min, float x_max, float y_min, float y_max)
{
	return ((x - x_min) / (x_max - x_min)) * (y_max - y_min) + y_min;
}

int PGA::calcPerlin(float x, float y)
{
	float val = 0.0;
	float freq = 1.0;
	float amp = 1.0;
	for (int i = 0; i < 12; i++)
	{
		val += perlinNoise2d(x * freq / GRID_SIZE, y * freq / GRID_SIZE) * amp;
		freq *= 2;
		amp /= 2;
	}
	val *= 1.2;
	if (val > 1.5f)
		val = 1.5f;
	else if (val < -1.5f)
		val = -1.5f;
	return ((int)mapRangeWithZero(val, -1, 1.5, 100, 250));
}

int PGA::calcPerlin(float x, float y, float z)
{
	float noiseValue = 0.0;
	float amp = 1.0;
	float frequency = 1.0;
	for (int i = 0; i < 7; i++) {
		noiseValue += perlinNoise3d(x * frequency / GRID_SIZE, y * frequency / GRID_SIZE, z * frequency / GRID_SIZE) * amp;
		frequency *= 2; // lacunarity controls frequency growth
		amp *= 2; // persistence controls amp decay
	}
	return (noiseValue < 0.2);
}
