#pragma once

struct Settings{
	Settings(int grid, int chunk, int calc, int seed, int maxflight, int width, int height) :
	GridSize(grid), ChunkSize(chunk), CalcRange(calc), Seed(seed), MaxFrameInFlight(maxflight), ScreenWidth(width), ScreenHeight(height)
	{};
	Settings(): GridSize(0), ChunkSize(0), CalcRange(0), Seed(0), MaxFrameInFlight(0), ScreenWidth(0), ScreenHeight(0) {};
	int GridSize;
	int ChunkSize;
	int CalcRange;
	int Seed;
	int MaxFrameInFlight;
	unsigned int ScreenWidth;
	unsigned int ScreenHeight;
};

class Env{
public:
	Env(Settings s) : setting(s) {}
	// Terrain1	mapManager;
	const Settings setting;
};

extern Env* env;
int InitSettings(char *arg);