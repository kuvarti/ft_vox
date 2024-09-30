#pragma once

#include "voxel.hpp"

void calcPerlin(Voxel &, float, float);
float perlin(float x, float y);
Vector2D randomGradient(int ix, int iy);
float dotGridGradient(int ix, int iy, float x, float y);
float interpolate(float a0, float a1, float w);

int **cellular(int xmi);
// void cellular(int **map1, int **map2);
unsigned randomVoxel(); //change the name;