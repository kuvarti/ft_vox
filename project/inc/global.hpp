#pragma once

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <array>
#include <tuple>
#include "Terrain.hpp"

class Env{
public:
	// Terrain1	mapManager;
	int			seed;
};

extern Env env;
namespace std {

	template <>
	struct hash<std::tuple<int, int>> {
		std::size_t operator()(const std::tuple<int, int>& key) const {
			return std::hash<int>()(std::get<0>(key)) ^ std::hash<int>()(std::get<1>(key));
		}
	};
	// template <>
	// struct hash<glm::vec2> {
	// 	std::size_t operator()(const glm::vec2& key) const {
	// 		return std::hash<int>()(key.x) ^ std::hash<int>()(key.y);
	// 	}
	// };
}


void doSomething(SDL_Renderer*, int, SDL_Texture*);