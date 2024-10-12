Harita uzerinde bulunan her bir block'un karsiligi. X, Y, Z ve Caves(magaralar) bilgilerinden olusur.
- X: `int`
- Y: `int`
- Z: `int`
- Caves: `std::list<std::tuple<int, int>>` tuple(Min, Max)

X, Y, Z icin getter setterlar bulunur.

Caves icin `AddCave`, `IsCave` ve `GetCaves` fonksiyonlari bulunur.
