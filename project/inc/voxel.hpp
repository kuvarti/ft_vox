#pragma once
#include "vector2D.hpp"

#define _CAVE_LIST std::list<Cave>

#define VOXEL_FACE_UP 1	   // 1 << 0
#define VOXEL_FACE_DOWN 2  // 1 << 1
#define VOXEL_FACE_NORTH 4 // 1 << 2
#define VOXEL_FACE_SOUTH 8 // 1 << 3
#define VOXEL_FACE_WEST 16 // 1 << 4
#define VOXEL_FACE_EAST 32 // 1 << 5

class Faces
{
public:
	Faces() { _faceFlags = 0; }
	Faces(unsigned char x) { _faceFlags = x; }
	Faces(const Faces &f) { _faceFlags = f._faceFlags; }
	Faces &operator=(const Faces &f)
	{
		if (&f != this)
			_faceFlags = f._faceFlags;
		return *this;
	}

	bool IsUp() const { return _faceFlags & VOXEL_FACE_UP; }
	bool IsDown() const { return _faceFlags & VOXEL_FACE_DOWN; }
	bool IsNorth() const { return _faceFlags & VOXEL_FACE_NORTH; }
	bool IsSouth() const { return _faceFlags & VOXEL_FACE_SOUTH; }
	bool IsWest() const { return _faceFlags & VOXEL_FACE_WEST; }
	bool IsEast() const { return _faceFlags & VOXEL_FACE_EAST; }

	unsigned char GetAllFaces() const { return _faceFlags; }

	void SetFace(unsigned char f) { _faceFlags |= f; }
	void ClearFace(unsigned char f) { _faceFlags &= ~f; }
	void SetFaceWithZero(unsigned char f) { _faceFlags = f; }
	void SetFaceZero() { _faceFlags = 0; }

private:
	unsigned char _faceFlags;
};

struct CaveWall
{
	CaveWall(int z)
	{
		this->z = z;
	}
	CaveWall(int z, unsigned char f)
	{
		this->z = z;
		face.SetFaceWithZero(f);
	}
	Faces face;
	int z;
};

struct Cave
{
	Cave(int wmin, int wmax) : min(CaveWall(wmin)), max(CaveWall(wmax)) {}
	Cave(int wmin, unsigned char minFaces, int wmax, unsigned char maxFaces) : min(CaveWall(wmin, minFaces)), max(CaveWall(wmax, maxFaces)) {}
	Cave(CaveWall wmin, CaveWall wmax) : min(wmin), max(wmax) {}
	CaveWall min, max;
};

class Voxel : public Faces
{
public:
	Voxel() : Faces()
	{
		_x = 0;
		_y = 0;
		_z = 0;
	}
	Voxel(int x, int y, int z) : Faces()
	{
		_x = x;
		_y = y;
		_z = z;
	}
	Voxel(const Voxel &v) : Faces(v.GetAllFaces())
	{
		_x = v._x;
		_y = v._y;
		_z = v._z;
		_caves = v._caves;
	}
	Voxel &operator=(const Voxel &v)
	{
		if (&v != this)
		{
			_x = v._x;
			_y = v._y;
			_z = v._z;
			_caves = v._caves;
			SetFaceWithZero(v.GetAllFaces());
		}
		return *this;
	};
	~Voxel()
	{
		while (!_caves.empty())
			_caves.pop_front();
	};

	void AddCave(int min, int max)
	{
		_caves.emplace_back(Cave(min, max));
	}
	void AddCave(CaveWall min, CaveWall max)
	{
		_caves.emplace_back(Cave(min, max));
	}
	_CAVE_LIST GetCaves()
	{
		return _caves;
	}
	_CAVE_LIST &GetAndChangeCaves()
	{
		return _caves;
	}

	int Get_x() const { return _x; }
	int Get_y() const { return _y; }
	int Get_z() const { return _z; }
	Vector2D Get_2dPos() const { return Vector2D(_x, _y); }

	int Set_x(int x)
	{
		_x = x;
		return _x;
	}
	int Set_y(int y)
	{
		_y = y;
		return _y;
	}
	int Set_z(unsigned z)
	{
		_z = z;
		return _z;
	}
	void Set_2dPos(int x, int y)
	{
		_x = x;
		_y = y;
	}
	void Set_2dPos(Vector2D v)
	{
		_x = v.Get_x();
		_y = v.Get_y();
	}

private:
	int _x;
	int _y;
	int _z;
	_CAVE_LIST _caves;
};
