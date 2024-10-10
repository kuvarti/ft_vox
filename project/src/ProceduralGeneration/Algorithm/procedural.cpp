#include "ProceduralGenerationAlgorithms.hpp"
#include "vector2D.hpp"
#include <math.h>

Vector2D PGA::randomGradient(int ix, int iy)
{
	const unsigned w = 8 * sizeof(unsigned);
	const unsigned s = w / 2;
	unsigned a = ix, b = iy;
	a *= 3284157443;
	b ^= a << s | a >> w - s;
	b *= 1911520717;
	a ^= b << s | b >> w - s;
	a *= 2048419325;
	float random = a * (3.14159265 / ~(~0u >> 1));

	Vector2D v;
	v.Set_x(sin(random));
	v.Set_y(cos(random));
	return v;
}

Vector3D PGA::randomGradient(int ix, int iy, int iz)
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
	float random = a * (3.14159265 / ~(~0u >> 1));

	Vector3D v;
	v.Set_x(sin(random));
	v.Set_y(cos(random));
	v.Set_z(sin(random * 1.5));
	return v;
}


float PGA::dotGridGradient(int ix, int iy, float x, float y)
{
	Vector2D gradient = randomGradient(ix, iy);
	float dx = x - (float)ix;
	float dy = y - (float)iy;
	return (dx * gradient.Get_x() + dy * gradient.Get_y());
}

float PGA::dotGridGradient(int ix, int iy, int iz, float x, float y, float z)
{
	Vector3D gradient = randomGradient(ix, iy, iz);
	float dx = x - (float)ix;
	float dy = y - (float)iy;
	float dz = z - (float)iz;

	return (dx * gradient.Get_x() + dy * gradient.Get_y() + dz * gradient.Get_y());
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