#pragma once

#include "vector2D.hpp"
#include "ProceduralGenerationAlgorithms.hpp"
#include "voxel.hpp"
#include <math.h>

#define GRID_SIZE	128
#define CHUNK_SIZE	16

class Chunk {
public:
	Chunk();
	Chunk(Vector2D);
	Chunk(float, float);
	~Chunk();

	Voxel	GetVoxelbyLocalCoordinate(Vector2D) const;
	Voxel	GetVoxelbyGlobalCoordinate(Vector2D) const;
	void	_GenerateTerrain(); //todo this gonna be private
	int	***_GenerateCave(); //todo this gonna be private

	void	Set_StartPoint(Vector2D v) {
		_startPoint.Set_x(v.Get_x());
		_startPoint.Set_y(v.Get_y());
	}
	void	Set_StartPoint(float x, float y) {
		_startPoint.Set_x(x);
		_startPoint.Set_y(y);
	}

	void	PrintVoxelInfo();
private:
	Vector2D	_startPoint;
	Voxel		**_voxel;
	int			_length;

};

float mapRangeWithZero(float x, float x_min, float x_max, float y_min, float y_max);