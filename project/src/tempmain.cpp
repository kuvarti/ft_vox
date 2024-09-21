#include "perlinNoise.hpp"
#include "global.hpp"
#include <unordered_map>
#include <chrono>

void	deneme() {
	const int start = -8192;
	const int end = 8192;
	const int step = 16;

	auto startTime = std::chrono::high_resolution_clock::now();
	std::unordered_map<std::tuple<int, int>, Chunk *> Chunks;

	bool overlapFound = false;
	for (int x = start; x <= end; x += step) {
		for (int y = start; y <= end; y += step) {
			auto currentCoord = std::make_tuple(x, y);
			if (Chunks.find(currentCoord) != Chunks.end()) {
				std::cout << "Overlap found at (" << x << ", " << y << ")" << std::endl;
				overlapFound = true;
				break;
			} else {
				// Chunks.insert_or_assign(std::make_tuple(x/16, y/16), new Chunk(x, y));
			}
			std::cout << "Chunk at (" << x/16 + x%16 << ", " << y/16 + y%16 << ") ("<< x << ", " << y <<") Created" << std::endl;
		}
	}
	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	std::cout << "Total number of chunks: " << Chunks.size() << std::endl;
	std::cout << "Time taken: " << duration << " milliseconds" << std::endl;
}