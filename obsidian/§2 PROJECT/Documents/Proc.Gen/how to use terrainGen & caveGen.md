
Terrain Generation chunk'in icerisinde otomatik generate ediliyor, bu sayede generation icin extra bir ugrasa gerek yok.

```cpp
class Chunk: public TerrainGen, public CaveGen
```

Chunk classini olusturuldugu anda dunya generate ediliyor. 
> ! Bu kisim onemli : Default constructor ```Chunk()``` ile olusturulan chunklar herhangi bir dunya generate etmez. Daha sonradan elle olusturulmasi gerekir.

Generationlar lokasyon bazli calistigi icin chunk'a startpoint vermek generation icin cok onemli. Bu yuzden otomatik world generation icin Chunk olustururken `(Vector2D)` veya `(float, float)` constructerlar ile baslangic pozisyonu ayarlanmali.
Ama default contructor cagirilmak zorunda ise daha sonradan ```ChangeStartPosition (Vector2D)``` ile baslangic pozisyonunu degistirip generasyon tetiklenebilir

> ! Cave Generation henuz hazir olmadigi icin yapiya tam olarak entegre edilmedi.

Chunk icerisindeki voxelleri butun olarak cagirilamaz. chunk olusturuldak sonra 
```cpp
Voxel GetVoxelByLocalCoordinate(Vector2D v) const;
Voxel GetVoxelByLocalCoordinate(int x, int y) const;
Voxel GetVoxelbyGlobalCoordinate(Vector2D) const;
Voxel GetVoxelbyGlobalCoordinate(int, int) const;
```
fonksiyonlarindan herhangi bir tane ile belirtilen kordinatdaki voxel cagirilabilir.
- **Local Coordinate**: Chunk icerisindeki koordinati verildiginde elde edilecek Voxel. 
	x ve y 0-16 araliginda olmasi, aksi taktirde (0,0,0) voxeli doner.
- **Global Coordinate:** !Onermiyorum. Tum uzay uzerindeki kordinatini local'e donusturup ilgili voxeli verir.
	x ve y chunk baslangicindan kucuk `chunk_baslangici + length` den buyuk olamaz, aksi takdirde (0,0,0) voxeli doner

## Fikir:
/todo herhangi bir sebep icin gerekli olursa voxelleri serit olarak cagiran bir get olabilir. Serit : [[Chunk1]]