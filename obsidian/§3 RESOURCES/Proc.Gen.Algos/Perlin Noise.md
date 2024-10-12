[pseudo-random](https://en.wikipedia.org/wiki/Pseudo-random "Pseudo-random") sekilde bir gurultu uretir. Bu sayede deterministik sekilde 'Rastgele' dunyalar olusturabilir. 

[[Simplex Noise]] gibi hem gerçek zamanlı grafikler hem de her türlü bilgisayar grafiğinde gerçek zamanlı olmayan prosedürel dokular için grafik işlem birimlerinde neredeyse her yerde bulunur hale gelmiştir. 

![png](https://upload.wikimedia.org/wikipedia/commons/thumb/8/88/Perlin_noise_example.png/600px-Perlin_noise_example.png)

## Algoritma 

1. İki boyutlu bir gradyan vektörlerinden olusan grid
	![Gradyan](https://upload.wikimedia.org/wikipedia/commons/thumb/3/37/PerlinNoiseGradientGrid.svg/1920px-PerlinNoiseGradientGrid.svg.png)
2. Her noktanın en yakın grid kesisimindeki gradyan değeri ile nokta çarpımı([[Dot Product]]).
	![dotProduct](https://upload.wikimedia.org/wikipedia/commons/thumb/a/a3/PerlinNoiseDotProducts.svg/1920px-PerlinNoiseDotProducts.svg.png)
3.  Yumusak gecisler icin enterpolasyonlu sonuç
	![Enterpolasyon](https://upload.wikimedia.org/wikipedia/commons/thumb/0/07/PerlinNoiseInterpolated.svg/1920px-PerlinNoiseInterpolated.svg.png)

