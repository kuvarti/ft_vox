#include "global.hpp"
#include "chunk.hpp"
#include "VulkanApp.hpp"

Env env;
int main()
{
	Chunk a(320, 320);
	srand(time(0));
	env.seed = rand();
	// env.seed = 1;
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