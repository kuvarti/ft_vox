#pragma once

#include "vector2D.hpp"
#include <math.h>

#define GRID_SIZE	300
#define CHUNK_SIZE	25

class	PerlinNoise {
public:
	PerlinNoise() { };
	~PerlinNoise() { };

	//Todo/ Bu perlin fonksiyonu gelecekte private olacak. direk perline erismek yerine
	//todo/ chunk verip butun chunk'i renderlayacak
	float perlin(float x, float y);
private:
	Vector2D randomGradient(int ix, int iy);
	float dotGridGradient(int ix, int iy, float x, float y);
	float interpolate(float a0, float a1, float w);
};
