
## General Instructions
- Herhangi bir dil kullanilabilir
- OpenGL ve Vulkan kullanilabilir ama bunlari kullanmak icin araya 3. bir kutuphane kullanmak yasak.
- 3D objeleri , resimleri ve pencereyi yonetebilmek; matrix/quaternions/vector hesaplamalarini yapmak icin kutuphaneler kullanlabilir.
- Oyun her zaman smooth olmak zorunda.
- Herhangi bir hata kabul edilemez.
- leak olmadan saatlerce calisabilmeli.
- Uygulama FullScreen modunca calismak zorunda.

## Mandatory
- Dunya 16384x256x16384 buyuklugunde olacak. (256 yukseklik)
- Bosluklar haric en az 2 farkli kup kullanmak zorunlu.
- Tepeler, Daglar ve magaralar olusturan kodlar eklenmeli.
- Deterministik bir random olmasi gerekiyor. Yani Ayni seed her azman ayni haritayi verecek.
- Zemin tepeler ve daglar ile uyumlu olmak zorunda ve Basit bir rand() fonksiyonu yetersiz.
- Belirli bir bolgeye kadar araziyi memoryde tutmak zorundayiz daha sonra silinebilir.

## Graphic rendering
- kupler ekranda gosterilmeli. Minimum render uzakligi her yone 160 kup.
- Her kupun bir texturesi olmak zorunda ve en az 2 farkli texture sahip kup olmali.
- FoVda her zaman birseyler olmali ve 80 derece olmali.
- skybox eklenmeli.

## The camera
- Mouse ile 2 eksende kontrol edilen ve 4 tusla klavye uzerinden ileri geri iyapabilen bir kamera eklenmeli.
-  Kameranin hizi 1kup/saniye olmali. Ama evo icin bir tus ekleyip x20 hizina cikmali.

## To sum it up:
- Farkli tipdeki kupler ile dolu devasa bir alan
- Genis bir FoV
- Dogal bir gorunum ureten gelismis bir procedural generation.
- Haraketli kamera
- Skybox

## Bonus
- FPS counter.
- Render Smooth olmak zorunda. x20de bile.
- Mouse ile block silinebilmeli.
- Cesitli Biomlar.
