#pragma once

#include "voxel.hpp"

int calcPerlin(float, float);
float perlin(float x, float y);
Vector2D randomGradient(int ix, int iy);
float dotGridGradient(int ix, int iy, float x, float y);
float interpolate(float a0, float a1, float w);

int **cellular(int xmi, int size);
// void cellular(int **map1, int **map2);
unsigned randomVoxel(); // todo change the name;