### - VulkanApp
Temel vulkan fonksiyonlarını içeren sınıfımız. 
```math
app.run();
```
Diyerek vulkan uygulamamızın çalışmasını sağlıyoruz. 

```initWindow():``` SDL kullanarak bir pencere oluşturur. SDL (Simple DirectMedia Layer), pencere ve giriş kontrolü için kullanılıyor. Bu fonksiyonla Vulkan destekli bir pencere oluşturuluyor.

```mainLoop():``` Ana oyun/uygulama döngüsünü yönetir. Bu fonksiyon tipik olarak sürekli çalışır ve olayları işler, görüntüyü çizer ve girdi ile etkileşimi sağlar


```initVulkan():```
![png](https://gpuopen.com/wp-content/uploads/2017/07/Vulkan-Diagram-568x1024.png)



### ```createInstance():``` 
```VkApplicationInfo``` yapısı, Vulkan'ın başlatılırken ihtiyaç duyduğu bazı uygulama bilgilerini içerir

```sdlExtensionCount:``` SDL ile Vulkan arasındaki eklenti sayısını tutan değişkendir.
```sdlExtensions:``` Eklentilerin isimlerini içeren bir vektördür. Bu isimler, Vulkan'ın belirli platformlarla çalışabilmesi için gerekli olan uzantıları içerir.

Bu uzantılar, Vulkan'ın pencere sistemiyle (örneğin SDL ile) nasıl çalışacağını bilmesi için gereklidir. Eğer bu uzantıları alamazsa, uygulama çalışmaz.
```vulkan instance:``` Vulkan Instance, uygulamanın Vulkan grafik sürücüsü ile etkileşim kurmasını sağlar. Her GPU üreticisinin Vulkan sürücüleri farklıdır ve uygulamanın bu sürücülerle sorunsuz iletişim kurabilmesi için bir Instance oluşturulması gereklidir. Instance, bu iletişimi kurmak için bir temel sağlar. Ayrıca donanım tespiti ve sdl uzantılarını tanımlama gibi işlemleri uygulamamızı sağlar

### ```SDL_Vulkan_CreateSurface():``` 
Vulkan ile SDL kullanarak bir pencere yüzeyi (surface) oluşturur. Bu yüzey, Vulkan'ın görüntü oluşturacağı platforma (pencereye) bağlanmasını sağlar.

### ```pickPhysicalDevice():``` 
 Bu fonksiyon, Vulkan destekli GPU'ları listeler, uygun olanını seçer ve Vulkan işlemlerinde kullanılmak üzere fiziksel cihazı belirler. 
```isDeviceSuitable()```seçilen physical device vulkan uygulaması için gerekli özelliklere sahip mi? sorgusunu yapar

### ```createLogicalDevice():``` 
seçilen fiziksel cihaz (GPU) üzerinde Vulkan işlemleri gerçekleştirmek için gereken cihazı (logical device) oluşturur. Mantıksal cihaz, fiziksel cihazın özelliklerini kullanarak Vulkan komutlarının yürütüleceği bir yapı sağlar. Vulkan'da işlemler doğrudan fiziksel cihaz üzerinde değil, mantıksal cihaz üzerinde yapılır.
``` VkDeviceQueueCreateInfo ``` Vulkan'da işlemleri yönetmek için komut kuyrukları (queues) kullanılır.
```vkGetDeviceQueue``` 
```graphicsQueue:``` Grafik işlemlerini yapacak kuyruk. Bu kuyruk grafiksel işlemleri yönetir.
```presentQueue:``` ekrana görüntü çıkışı yapılmasını sağlar.

### ```createSwapChain():``` 
 Swap Chain, uygulamanın GPU ile çalışmasını sağlayan ve arka planda işlenmiş görüntülerin ekrana yansıtılması için kullanılan bir yapıdır. Bir Swap Chain, görüntülerin arka planda (frame buffer'da) oluşturulmasını sağlar ve bu görüntüleri ekrana (surface'e) yansıtır.
```vkGetPhysicalDeviceSurfaceCapabilitiesKHR:``` Bu fonksiyon, fiziksel cihazın (GPU'nun) yüzey (surface) üzerindeki yeteneklerini alır. Yani, GPU'nun bu yüzeyde nasıl görüntü oluşturacağını öğrenmek için kullanılır. 
```capabilities```GPU'nun yüzeyde neleri yapabileceğini ve sınırlarını içerir. Örneğin, minimum ve maksimum görüntü sayısı, görüntü boyutları, dönüşüm yetenekleri vb.

```VkSwapchainCreateInfoKHR:``` Bu yapı, swap chain'in nasıl oluşturulacağını tanımlar. İçerisinde, swap chain'in kaç adet görüntü oluşturacağı, hangi formatları kullanacağı, hangi boyutlarda olacağı gibi ayarlar bulunur.

```imageFormat:``` Swap chain tarafından kullanılacak görüntü formatını belirtir. Burada VK_FORMAT_B8G8R8A8_SRGB kullanılmış, yani 8-bit mavi, yeşil, kırmızı ve alfa kanalıyla birlikte sRGB renk alanı kullanılıyor. Bu format, renk doğruluğu ve doğrusal olmayan renk dönüşümleri için uygundur.

```imageColorSpace:``` Görüntünün renk uzayını belirtir. Burada VK_COLOR_SPACE_SRGB_NONLINEAR_KHR kullanılmış, bu da sRGB renk alanını ve doğrusal olmayan bir renk dönüşümünü ifade eder.

```imageSharingMode:``` Görüntülerin hangi işlemciler arasında paylaşılacağını belirtir. Burada VK_SHARING_MODE_EXCLUSIVE kullanılmış, bu da görüntülerin yalnızca tek bir kuyruk ailesi tarafından kullanılacağını ifade eder. Bu genellikle en hızlı yöntemdir.

```preTransform:``` Görüntüye önceden uygulanacak bir dönüşümü belirtir. Burada, capabilities.currentTransform ile yüzeyin şu anki dönüşümü kullanılıyor, yani herhangi bir ekstra dönüşüm yok.

```compositeAlpha:``` Alfa bileşeni ile ilgili ayar. VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR, görüntünün saydam olmayacağını, opak olacağını ifade eder.

```presentMode:``` Swap chain'in görüntüleri ekrana nasıl sunacağını tanımlar. VK_PRESENT_MODE_FIFO_KHR seçeneği kullanılmış, bu da görüntülerin sabit aralıklarla (genellikle ekranın yenileme hızıyla senkronize olarak) ekrana gönderileceğini belirtir. FIFO modunda ekran yırtılması önlenir.

```clipped:``` VK_TRUE değeri ile swap chain, ekranda görünmeyen piksellerin işlenmeyeceğini belirtir. Bu performans açısından avantaj sağlar.

```vkGetSwapchainImagesKHR:``` Swap chain tarafından kullanılan görüntüleri alır. İlk çağrıda, swap chain'in kaç adet görüntü içerdiği öğrenilir, ardından bu görüntüler swapChainImages dizisine doldurulur.

vkGetSwapchainImagesKHR fonksiyonunun iki kez çağrılmasının sebebi, Vulkan'da yaygın bir uygulama olan iki aşamalı sorgu (two-pass query) yöntemidir:

İlk çağrıda, swap chain'deki görüntü sayısı öğrenilir (yani imageCount elde edilir).
İkinci çağrıda, bu sayıya göre swap chain görüntüleri alınır (diziye görüntülerin bilgileri doldurulur).
Bu iki aşamalı süreç, dinamik bellek yönetimi sağlar ve bellek tahsisini optimize eder. Yani, ilk çağrı bellek ayırmadan sadece kaç tane görüntü olduğunu öğrenmek içindir, ikinci çağrı ise bu sayıya göre bellek ayırır ve görüntüleri alır.

### ```createImageViews():``` 
Bu fonksiyon, swap chain tarafından kullanılan görüntüler için image view (görüntü görünümü) oluşturur. Vulkan'da, image view, bir görüntünün (image) GPU üzerinde nasıl erişileceğini ve kullanılacağını belirten bir yapıdır. Image view'lar, görüntülerin işlenme sırasında nasıl görüneceğini, hangi kanalların (renk kanalları, alfa kanalı vb.) nasıl kullanılacağını tanımlar.

### ```createRenderPass():``` 
Bu fonksiyon, Vulkan'da bir Render Pass (çizim geçişi) oluşturur. Render Pass, grafik işleme sırasında bir veya birden fazla ek bileşen (attachment) üzerinde yapılan işlemleri tanımlayan bir yapıdır. Bu bileşenler genellikle bir görüntü (image) veya çerçeve arabelleğidir (framebuffer). Render Pass, sahneyi nasıl işleneceğini ve hangi görüntülerin kullanılacağını belirler.

``` colorAttachment``` Vulkan'da render pass içerisinde bir renk eki (attachment) olarak kullanılan bir yapıdır. Renk ekleri, görüntülerin çizim işlemleri sırasında nasıl kullanılacağını ve saklanacağını belirleyen bileşenlerdir.

### ```createDescriptorSetLayout():``` 
Vulkan grafik API'sinde bir descriptor set layout oluşturmak için gerekli adımları içerir. Bu işlem, shader programlarına (genellikle bir grafik pipeline'ında kullanılan kod parçaları) veri göndermek için gereklidir. 

Vulkan'da, shader programlarıyla etkileşimde bulunmak için verileri tanımlamanız ve düzenlemeniz gerekiyor. Bu veriler, genellikle matrisler, dokular, veya diğer veriler gibi GPU'nun işlediği verileri içerir. Bu verileri shader'lara iletmek için descriptor set adında yapılar kullanılır. Descriptor set layout ise bu descriptor set'lerin nasıl yapılandırılacağını belirten bir şablondur. Yani, hangi türde verilerin (uniform buffer, texture vs.) shader'a gönderileceğini tanımlar.

### ```createGraphicsPipeline():``` 
Vulkan grafik API'si kullanarak bir grafik pipeline oluşturur. Bu pipeline, vertex ve fragment shader'larını kullanarak sahnedeki nesnelerin nasıl çizileceğini tanımlar. Shader kodlarını okur, shader modüllerini oluşturur, vertex girdisi, viewport, rasterizasyon, multisampling ve renk karıştırma ayarlarını yapar. Son olarak, tüm bu bileşenleri birleştirerek bir grafik pipeline oluşturur ve kullanımdan sonra shader modüllerini temizler. Bu işlem, sahnede grafiklerin doğru bir şekilde görüntülenmesi için kritik öneme sahiptir.

```Vertex Shader``` Sahnedeki nesnelerin konumlarını hesaplar ve ekranda doğru bir şekilde yerleştirilmesini sağlar. Bu işlem, dönüşüm matrislerini kullanarak her vertex'in yerini belirler.
```Fragment Shader```Her pikselin rengini belirler. Renk hesaplamaları ve görsel efektler için kullanılır.



```Viewport:``` Ekranda hangi alana çizim yapılacağını belirtir.
```Scissor:``` Çizim alanını sınırlar, böylece sadece belirli bir bölgeye çizim yapılır.

```VkGraphicsPipelineCreateInfo``` Graphics Pipeline: Tüm önceki bileşenlerin birleştirildiği yapı. Bu yapı, render pass ile ilişkilendirilir ve oluşturulan vertex ve fragment shader'ları kullanılır.

### ```createFramebuffers():``` 
render pass'ları ile birlikte çalışmak üzere gerekli framebuffer nesnelerini oluşturur. Aşağıda bu fonksiyonun detaylı açıklamasını bulabilirsin.

Framebuffer, bir render pass sırasında kullanılmak üzere tasarlanmıştır. Render pass, hangi görüntülerin hangi sırayla ve hangi işlemlerle oluşturulacağını belirler.

Framebuffer'lar, görüntü verimliliğini artırmak ve grafik işleme sürecini optimize etmek için kullanılır. Her bir görüntü (image view) için ayrı bir framebuffer oluşturarak, sahnedeki nesnelerin ayrı ayrı işlenmesine olanak tanır.

 Framebuffer, grafik pipeline'ında render edilen verilerin son çıktısını belirler. Render işlemleri tamamlandıktan sonra, framebuffer'daki görüntüler ekrana veya bir dosyaya aktarılabilir.

### ```vkCreateCommandPool():``` 
GPU'ya gönderilecek komutları oluşturmak için bir komut havuzu (command pool) oluşturur. Komut havuzu, komutların topluca yönetilmesine olanak tanır.

### ```createVertexBuffer():``` 
Vertex buffer, grafik sahnelerinde görüntülenmesi gereken nesnelerin vertex verilerini depolamak için gereklidir. Bu veriler, şekil, konum, renk gibi özellikleri içerir. Vertex buffer, grafik pipeline'ında vertex verilerinin nasıl işleneceğini tanımlayan temel bileşenlerden biridir. Render işlemlerinde bu veriler kullanılarak sahneler oluşturulur.

### ```createIndexBuffer():```
bir indeks buffer oluşturmak, verileri bu buffer'a kopyalamak ve grafik nesnelerin işlenmesi için gerekli indeks verilerini sağlamak amacıyla kullanılır.

### ```createUniformBuffer():```
Uniform buffer'lar, vertex ve fragment shader'lara (ve diğer shader türlerine) veri iletmek için kullanılır. Örneğin, bir modelin dünya, görünüm ve projeksiyon matrisleri gibi veriler uniform buffer içinde saklanır. Ayrıca, CPU tarafından dinamik olarak güncellenebilir. Bu, oyun içi nesnelerin konumları veya diğer özellikleri değiştiğinde shader'lara yeni verilerin iletilmesini kolaylaştırır.

### ```Descriptor:```
 Descriptor setleri, uniform buffer'lar ve diğer kaynaklar arasında veri iletmek için kullanılır. Bu, shader'ların çalışması için gerekli olan verileri almasını sağlar.

### ```createCommandBuffers():```
Vulkan uygulamalarında render işlemlerini gerçekleştirmek için gereken command buffers larını oluşturur ve kaydeder. Bu, grafik işleme sürecinin önemli bir parçasıdır ve yüksek performans sağlar.

### ```createSyncObjects():```
Vulkan, CPU ve GPU arasında veri akışını kontrol etmek için semaforlar ve sınırlar (fences) kullanır. Bu, bir çerçevenin GPU tarafından işlenmeden önce görüntü verisinin mevcut olduğunu ve render işleminin tamamlandığını garanti eder. cpu ve gpu arasında senkronizasyon sağlar.



```mainloop():```
### ```updateUniformBuffer():```
UBO, model, görünüm ve projeksiyon matrislerini tutarak, nesnelerin ekranda doğru bir şekilde görüntülenmesini sağlar. kısaca Vulkanda 3D nesnelerin görünümünü ve perspektifini kontrol eden matrisleri dinamik olarak güncelleyerek, doğru ve etkili bir render işlemi sağlamak için gereklidir.

### ```drawFrame():``` 
```vkQueueSubmit()``` Komut buffer'ını GPU'ya gönderir. Eğer gönderim başarısız olursa bir hata fırlatır.

kısaca frame çizdiriyor :)

### ```vkDeviceWaitIdle():```
 Uygulama kapatılmadan önce, GPU'nun tüm işlemleri tamamlamasını bekler. Bu, kaynakların doğru bir şekilde serbest bırakılmasını ve uygulamanın düzgün bir şekilde kapanmasını sağlar.