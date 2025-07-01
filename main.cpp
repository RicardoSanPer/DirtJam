#include <iostream>

//Required to override SDL's default main
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <vulkan/vulkan.h>

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

int main(int argc, char* argv[])
{
	//Initializes the video subsystem
	SDL_Init(SDL_INIT_VIDEO);
	//Loads vulkan lib
	SDL_Vulkan_LoadLibrary(nullptr);
	//create window
	SDL_Window* window = SDL_CreateWindow("Dirt Jam", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);
	
	uint32_t extensionCount = 0;

	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::cout << extensionCount << " extensions supported" << std::endl;

	glm::mat4 matrix;
	glm::vec4 vec;
	auto test = matrix * vec;

	SDL_Event windowEvent;
	bool isRunning = true;

	//Main loop
	while (isRunning)
	{
		while (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
			{
				isRunning = false;
				break;
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Vulkan_UnloadLibrary();
	SDL_Quit();

	SDL_Log("Finished with errors: %s", SDL_GetError());

	return 0;
}