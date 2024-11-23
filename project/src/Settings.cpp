#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include "Settings.hpp"

Env* env = nullptr;
int InitSettings(char *arg)
{
	srand(time(0));
	std::string file(arg);
	Settings tmp;

	if (file.empty())
		file = "./settings";
	std::ifstream settingsFile(file);
	if (!settingsFile.is_open()) {
		std::cout << "Error: Could not open settings file or doesnt find default settings file.\n\tProgram will continue with default settings." << std::endl;
		env = new Env(Settings(128, 16, 10, rand(), 2, 800, 600, 1.0f));
		return 2;
	}
	std::unordered_map<std::string, int> settingsMap;
	std::string line;

	while (std::getline(settingsFile, line)) {
		std::istringstream lineStream(line);
		std::string key;
		int value;

		if (lineStream >> key >> value) {
			settingsMap[key] = value; 
		}
	}
	env = new Env(Settings(
		settingsMap.find("GRID_SIZE") != settingsMap.end() ? settingsMap["GRID_SIZE"] : 128,
		settingsMap.find("CHUNK_SIZE") != settingsMap.end() ? settingsMap["CHUNK_SIZE"] : 16,
		settingsMap.find("CALC_RANGE") != settingsMap.end() ? settingsMap["CALC_RANGE"] : 10,
		settingsMap.find("SEED") != settingsMap.end() ? settingsMap["SEED"] == 0 ? rand() : settingsMap["SEED"] : rand(),
		settingsMap.find("MAX_FRAMES_IN_FLIGHT") != settingsMap.end() ? settingsMap["MAX_FRAMES_IN_FLIGHT"] : 2,
		settingsMap.find("WIDTH") != settingsMap.end() ? settingsMap["WIDTH"] : 800,
		settingsMap.find("HEIGHT") != settingsMap.end() ? settingsMap["HEIGHT"] : 600,
		settingsMap.find("CUBE_SIZE") != settingsMap.end() ? settingsMap["CUBE_SIZE"] : 1.0f
	));
	settingsFile.close();
	if (env == NULL)
		return 0;
	return 1;
}