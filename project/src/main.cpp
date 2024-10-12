#include "global.hpp"
#include "chunk.hpp"

int main(int argc, char *argv[])
{
	// SDL başlatılıyor
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL başlatılamadı: " << SDL_GetError() << std::endl;
		return -1;
	}

	// SDL penceresi oluşturuluyor
	SDL_Window *window = SDL_CreateWindow("SDL2 ve Vulkan Test 1",
										  SDL_WINDOWPOS_CENTERED,
										  SDL_WINDOWPOS_CENTERED,
										  800, 800,
										  SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cerr << "Pencere oluşturulamadı: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return -1;
	}

	// Vulkan instance oluşturuluyor
	VkInstance instance;
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "SDL2 Vulkan Test";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	// SDL'in Vulkan ile kullanacağı gerekli uzantılar alınıyor
	unsigned int extensionCount = 0;
	if (!SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, nullptr))
	{
		std::cerr << "SDL Vulkan uzantıları alınamadı: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	std::vector<const char *> extensions(extensionCount);
	if (!SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, extensions.data()))
	{
		std::cerr << "SDL Vulkan uzantıları alınamadı (veri ile): " << SDL_GetError() << std::endl;
	}
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	// Vulkan instance oluşturuluyor
	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
	{
		std::cerr << "Vulkan instance oluşturulamadı!" << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	// Pencerenin Vulkan surface'i oluşturuluyor
	VkSurfaceKHR surface;
	if (!SDL_Vulkan_CreateSurface(window, instance, &surface))
	{
		std::cerr << "Vulkan surface oluşturulamadı: " << SDL_GetError() << std::endl;
		vkDestroyInstance(instance, nullptr);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	std::cout << "SDL2 ve Vulkan başarılı bir şekilde çalışıyor." << std::endl;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		SDL_DestroyWindow(window);
		std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 800, 600);
	if (texture == nullptr) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		std::cerr << "SDL_CreateTexture Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	int x = 0, lx = 1;

	// SDL penceresi açıkken basit bir döngü
	bool isRunning = true;
	SDL_Event event;
	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}
			if (event.type == SDL_KEYDOWN){
				if(event.key.keysym.sym == SDLK_ESCAPE)
					isRunning = false;
				else if(event.key.keysym.sym == SDLK_UP)
					x++;
				else if(event.key.keysym.sym == SDLK_DOWN)
					x--;
			}
		}

		if (x < 0) x = 0;
		if (x >= 16) x = 15;
		if (x != lx) {
			lx = x;
			Uint32* pixels = newRender(x);
			SDL_UpdateTexture(texture, NULL, pixels, 800 * sizeof(Uint32));
			delete pixels;
			printf("X: %d\n", x);
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		SDL_Delay(300);
	}

	// Temizleme işlemleri
	vkDestroySurfaceKHR(instance, surface, nullptr);
	vkDestroyInstance(instance, nullptr);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}