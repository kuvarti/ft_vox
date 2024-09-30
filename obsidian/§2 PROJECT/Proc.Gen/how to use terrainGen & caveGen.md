Terrain Generation chunk'in icerisinde otomatik generate ediliyor, bu sayede generation icin extra bir ugrasa gerek yok.

```cpp
class Chunk: public TerrainGen, public CaveGen
```

Chunk classini olusturuldugu anda dunya generate ediliyor. 
> ! Bu kisim onemli : Default constructor ```Chunk()``` ile olusturulan chunklar herhangi bir dunya generate etmez. Daha sonradan elle olusturulmasi gerekir.

Generationlar lokasyon bazli calistigi icin chunk'a startpoint vermek generation icin cok onemli. Bu yuzden otomatik world generation icin Chunk olustururken `(Vector2D)` veya `(float, float)` constructerlar ile baslangic pozisyonu ayarlanmali.
Ama default contructor cagirilmak zorunda ise daha sonradan ```ChangeStartPosition (Vector2D)``` ile baslangic pozisyonunu degistirip generasyon tetiklenebilir

Cave Generation henuz hazir olmadigi icin yapiya tam olarak entegre edilmedi.