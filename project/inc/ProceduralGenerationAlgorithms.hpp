#pragma once

#include "voxel.hpp"

namespace PGA {
//Procedural
Vector2D randomGradient(int, int);
Vector3D randomGradient(int, int, int);

float dotGridGradient(int, int, float, float);
float dotGridGradient(int, int, int, float, float, float);

float interpolate2d(float, float, float);
float interpolate3d(float a0, float a1, float w);

//Generation
int calcPerlin(float, float);
int calcPerlin(float, float, float);

float perlinNoise2d(float, float);
float perlinNoise3d(float, float, float);

unsigned randomVoxel(); // todo change the name;
}