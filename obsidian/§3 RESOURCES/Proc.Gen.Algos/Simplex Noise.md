**Simplex Noise:**

Pseudo-random şekilde bir gürültü üretir ve Perlin Noise'un bir alternatifidir. Daha az hesaplama yükü ve daha az yönsel artefakt ile yüksek boyutlarda çalışır.

**Simplex Noise'un Perlin Noise'a Göre Avantajları:**

- **Daha Düşük Hesaplama Karmaşıklığı:** Daha az çarpma işlemi gerektirir ve hesaplama maliyeti düşüktür.
- **Yüksek Boyutlara Ölçeklenebilirlik:** 4D ve 5D gibi yüksek boyutlarda, klasik Perlin Noise'a göre çok daha az hesaplama maliyetiyle çalışır.
- **Yönsel Artefaktların Azlığı:** Görsel olarak izotropiktir ve belirgin yönsel artefaktlara sahip değildir.
- **Sürekli ve İyi Tanımlanmış Gradyanlar:** Gradyanlar her yerde iyi tanımlanmıştır ve hesaplaması oldukça ucuzdur.
- **Donanımda Kolay Uygulanabilirlik:** Basit yapısı sayesinde donanım üzerinde kolayca implement edilebilir.

**Algoritma Detayı:**

Simplex Noise genellikle iki, üç veya dört boyutlu fonksiyonlar olarak uygulanır ancak herhangi bir boyut sayısı için tanımlanabilir. Bir uygulama genellikle şu dört adımı içerir:

1. **Koordinat Eğriltme:**
   Giriş koordinatı, A\*_n kafesine yerleştirilmek üzere dönüştürülür. Bu dönüşüm, hiperkübik bir yapı olan kafesin ana çaprazı boyunca sıkıştırılmasıyla elde edilir.

2. **Simpleks Bölme:**
   Dönüştürülen koordinatlar azalan sırada sıralanarak, noktanın içinde bulunduğu simpleks belirlenir. Bu, noktanın hangi n-boyutlu üçgende (simpleks) olduğunu saptamaya yarar.

3. **Gradyan Seçimi:**
   Her simpleks köşesi, bir pseudo-random gradyan yönüne dönüştürülür. Bu gradyanlar, gürültünün pseudo-random doğasını sağlar.

4. **Çekirdek Toplamı:**
   Her köşenin katkısı, radyo simetrik çekirdeklerin toplamıyla hesaplanır. Bu işlem, her köşenin gürültü değerine katkısını belirler ve son gürültü değeri bu katkıların toplamıyla bulunur.
