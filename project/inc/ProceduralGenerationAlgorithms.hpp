#pragma once

#include "Voxel.hpp"

namespace PGA
{
	// Procedural
	glm::vec2 randomGradient(int, int);
	glm::vec3 randomGradient(int, int, int);

	float dotGridGradient(int, int, float, float);
	float dotGridGradient(int, int, int, float, float, float);

	float interpolate2d(float, float, float);
	float interpolate3d(float a0, float a1, float w);

	// Generation
	int calcPerlin(float, float);
	int calcPerlin(float, float, float);

	float perlinNoise2d(float, float);
	float perlinNoise3d(float, float, float);

	unsigned randomVoxel(); // todo change the name;
}