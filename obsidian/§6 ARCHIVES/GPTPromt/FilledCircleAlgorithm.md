0 noktasinin dunyanin ortasi olan bir haritada(x,y(min):-8192 | x,y(max):8192), 
herhangi bir noktada: yaricapi 10 birim olan ICI DOLU!! daire olustur. 
doldurulmasi gereken asagidaki yapi. vec2 icerisine x ve y locasyonunu yerlestir ve her x, y locasyonu icin chunk * olustur.

chunk icerisine `new Chunk(x, y);` seklinde ekleme yap. `_chunk_list.emplace(glm::vec2(x / 16, y / 16), new Chunk(glm::vec2(x, y)))`
std::unordered_map<glm::vec2, Chunk *, Vec2Hash, Vec2Equal> _chunk_list;

eski kare seklinde alan dolduran kodum asagida, buna benzer bir yapi kurarsan benim icin daha iyi olur.
```cpp
void Terrain::_InitMap(glm::vec2 camera)
{
	_pivot.x = (int)(camera.x / 16) * 16;
	_pivot.y = (int)(camera.y / 16) * 16;

	int xMax = _pivot.x + (10 * CHUNK_SIZE);
	int yMax = _pivot.y + (10 * CHUNK_SIZE);
	glm::vec2 it;
	it.x = (int)_pivot.x - (10 * CHUNK_SIZE);
	it.y = (int)_pivot.y - (10 * CHUNK_SIZE);
	for (; it.x <= xMax; it.x += CHUNK_SIZE)
	{
		for (it.y = (int)_pivot.y - (10 * CHUNK_SIZE); it.y <= yMax; it.y += CHUNK_SIZE)
		{
			_chunk_list.emplace(glm::vec2(it.x / 16, it.y / 16), new Chunk(it));
		}
	}
}
```
![[FilledCircleAlgorithm.png]]