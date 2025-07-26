#define SDL_MAIN_HANDLED
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include "VulkanApp.h"

const int size = 20;

//std::vector<Vertex> vertices = {
//	{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
//	{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
//	{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
//	{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}},
//};
//std::vector<uint16_t> indices =
//{
//	0, 1, 2, 2, 3, 0
//};

std::vector<Vertex> vertices;
std::vector<uint16_t> indices;

int main(int argc, char* argv[])
{
	VulkanApp app;
	try
	{
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}