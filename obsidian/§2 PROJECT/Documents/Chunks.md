Harita bu class icinde 16x16 seklinde saklanir.

TerrainGen ve CaveGenden miras alir bu sayede extra ugras vermeden dunya olusturma islemlleri uygulamabilir.

Generation islemlerini surdurmek icin startpoint'e ihtiyaci var.

Voxellere erisim ve generation kurallari icin: [[how to use terrainGen & caveGen]]

```cpp
class WorldGen
{
public:
	WorldGen(int x, int y);
	~WorldGen();
	Voxel& GetVoxelByLocalCoordinate(Vector2D v) const;
	Voxel& GetVoxelByLocalCoordinate(size_t x, size_t y) const;
protected:
	virtual void Generate(Vector2D) = 0;
	void SetVoxelByLocalCoordinaate(Vector2D v, Voxel voxel);
	Vector2D GetLength() const;
private:
	Voxel **_map;
	Vector2D _len;
};

class TerrainGen : virtual public WorldGen
{
public:
	TerrainGen(Vector2D);
	~TerrainGen();
protected:
	void Generate(Vector2D) override;
};

class CaveGen : virtual public WorldGen
{
public:
	CaveGen(Vector2D);
	~CaveGen();
protected:
	void Generate(Vector2D) override;
private:
	void SeperateCaves(int *, Vector2D);
};

class Chunk : public TerrainGen, public CaveGen
{
public:
	Chunk();
	Chunk(Vector2D);
	Chunk(float, float);
	~Chunk();

	void ChangeStartPosition(Vector2D);
	Voxel GetVoxelbyGlobalCoordinate(Vector2D) const;
	Voxel GetVoxelbyGlobalCoordinate(int, int) const;
	void PrintVoxelInfo();
protected:
	void Generate(Vector2D v) override {
		TerrainGen::Generate(v);
		CaveGen::Generate(v);
	}
private:
	Vector2D _startPoint;
	int _length;
};
```