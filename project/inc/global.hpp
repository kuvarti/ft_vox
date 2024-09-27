#pragma once

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>

namespace std {
	template <>
	struct hash<std::tuple<int, int>> {
		std::size_t operator()(const std::tuple<int, int>& key) const {
			return std::hash<int>()(std::get<0>(key)) ^ std::hash<int>()(std::get<1>(key));
		}
	};
}

void deneme();
Uint32 *newRender(int x);

//8704