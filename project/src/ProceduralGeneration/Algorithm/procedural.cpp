#include "ProceduralGenerationAlgorithms.hpp"
#include "global.hpp"
#include <math.h>

glm::vec2 PGA::randomGradient(int ix, int iy)
{
	const unsigned w = 8 * sizeof(unsigned);
	const unsigned s = w / 2;
	unsigned a = ix, b = iy;
	a *= 3284157443;
	b ^= a << s | a >> w - s;
	b *= 1911520717;
	a ^= b << s | b >> w - s;
	a *= 2048419325;
	a *= env.seed;
	float random = a * (3.14159265 / ~(~0u >> 1));

	glm::vec2 v;
	v.x = sin(random);
	v.y = cos(random);
	return v;
}

glm::vec3 PGA::randomGradient(int ix, int iy, int iz)
{
	const unsigned w = 8 * sizeof(unsigned);
	const unsigned s = w / 3;
	unsigned a = ix, b = iy, c = iz;
	a *= 3284157443;
	b ^= a << s | a >> (w - s);
	b *= 1911520717;
	c ^= b << s | b >> (w - s);
	c *= 2048419325;
	a ^= c << s | c >> (w - s);
	a *= env.seed;
	float random = a * (3.14159265 / ~(~0u >> 1));

	glm::vec3 v;
	v.x = sin(random);
	v.y = cos(random);
	v.z = sin(random * 1.5);
	return v;
}

float PGA::dotGridGradient(int ix, int iy, float x, float y)
{
	glm::vec2 gradient = randomGradient(ix, iy);
	float dx = x - (float)ix;
	float dy = y - (float)iy;
	return (dx * gradient.x + dy * gradient.y);
}

float PGA::dotGridGradient(int ix, int iy, int iz, float x, float y, float z)
{
	glm::vec3 gradient = randomGradient(ix, iy, iz);
	float dx = x - (float)ix;
	float dy = y - (float)iy;
	float dz = z - (float)iz;

	return (dx * gradient.x + dy * gradient.y + dz * gradient.y);
}

float PGA::interpolate2d(float a0, float a1, float w)
{
	return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}

float PGA::interpolate3d(float a0, float a1, float w)
{
	// You can use smootherstep for smoother interpolation
	// w = w * w * w * (w * (w * 6 - 15) + 10);
	return a0 + w * (a1 - a0);
}