#include "chunk.hpp"
#include "iostream"

Chunk::Chunk() {
	_startPoint.Set_x(0);
	_startPoint.Set_y(0);
	_length = CHUNK_SIZE;

	_voxel = new Voxel*[_length];
	for (int i = 0; i < _length; ++i) {
		_voxel[i] = new Voxel[_length];
	}
	std::cout << "Chunk::Chunk() Called" << std::endl;
}

Chunk::Chunk(Vector2D startPoint) {
	_startPoint = startPoint;
	_length = CHUNK_SIZE;

	_voxel = new Voxel*[_length];
	for (int i = 0; i < _length; ++i) {
		_voxel[i] = new Voxel[_length];
	}
	_GenerateTerrain();
}

Chunk::Chunk(float x, float y) {
	_startPoint.Set_x(x);
	_startPoint.Set_y(y);
	_length = CHUNK_SIZE;

	_voxel = new Voxel*[_length];
	for (int i = 0; i < _length; ++i) {
		_voxel[i] = new Voxel[_length];
	}
	// _GenerateTerrain();
	std::cout << "Chunk::Chunk(float, float) Called" << std::endl;
}

Chunk::~Chunk() {
	for (int i = 0; i < _length; ++i) {
		delete[] _voxel[i];
	}
	delete[] _voxel;
}

Voxel Chunk::GetVoxelbyLocalCoordinate(Vector2D v) const{
	return _voxel[(int)v.Get_x()][(int)v.Get_y()];
}

Voxel Chunk::GetVoxelbyGlobalCoordinate(Vector2D v) const{
	return _voxel
		[(int)(v.Get_x()+_startPoint.Get_x())]
		[(int)(v.Get_y()+_startPoint.Get_y())];
}

void Chunk::_GenerateTerrain() {
	for (size_t x = 0; x < _length; x++) //0
	{
		for (size_t y = 0; y < _length; y++) //0
		{
			calcPerlin(_voxel[x][y], _startPoint.Get_x() + x, _startPoint.Get_y() + y);
		}
	}
}

void Chunk::_GenerateCave() {
	// cellular();
	for (size_t x = 0; x < _length; x++) //0
	{
		for (size_t z = 0; z < _length; z++) //0
		{
			for (size_t x = 30; x < 100; x++)
			{
				/* code */
			}
		}
	}
}

void	Chunk::PrintVoxelInfo(){
	printf("Chunk (%d)-(%d):\n", (int)_startPoint.Get_x(), (int)_startPoint.Get_y());
	for (size_t x = 0; x < _length; x++)
	{
		for (size_t y = 0; y < _length; y++)
		{
			printf("\tX:%ld, Y:%ld - Voxel Pos: (%d)-(%d)-(%d)\n", x, y, _voxel[x][y].Get_x(), _voxel[x][y].Get_y(), _voxel[x][y].Get_z());
		}
	}
}