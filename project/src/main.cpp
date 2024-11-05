#include "Global.hpp"
#include "Chunk.hpp"
#include "VulkanApp.hpp"

#include <iostream>

int main(int argc, char **argv)
{
	if (!InitSettings(argv[1]))
		return 1;
	VulkanApp app;
	try
	{
		app.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}