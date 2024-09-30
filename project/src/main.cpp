#include "global.hpp"
#include "chunk.hpp"

void deneme();
int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL başlatılamadı: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_Window *window = SDL_CreateWindow("SDL2 ve Vulkan Test 1",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800,
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

	int x = 0, lx = 1;
	Chunk a;
	a._GenerateCave();

	// deneme();
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
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		SDL_Delay(300);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
