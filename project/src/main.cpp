#include "global.hpp"
#include "perlinNoise.hpp"

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL başlatılamadı: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_Window *window = SDL_CreateWindow("SDL2 ve Vulkan Test 1",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
		SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cerr << "Pencere oluşturulamadı: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return -1;
	}

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

	PerlinNoise p;
	Uint32* pixels = new Uint32[800 * 600];
	for (size_t x = 0; x < 800; x++) {
		for (size_t y = 0; y < 600; y++) {
			float val = 0;
			float freq = 1;
			float amp = 1;
			for (int i = 0; i < 12; i++) {
				val += p.perlin(x * freq / GRID_SIZE, y * freq / GRID_SIZE) * amp;
				freq *= 2;
				amp /= 2;
			}
			val *= 1.2;
			if (val > 1.0f)
				val = 1.0f;
			else if (val < -1.0f)
				val = -1.0f;
			int color = (int)(((val + 1.0f) * 0.5f) * 255);
			pixels[y * 800 + x] = (color << 24) | (color << 16) | (color << 8) | color;
		}
	}
	SDL_UpdateTexture(texture, NULL, pixels, 800 * sizeof(Uint32));

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
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
