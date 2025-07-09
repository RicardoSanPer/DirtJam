#define SDL_MAIN_HANDLED

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
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			vertices.push_back({ 
				{((float)i / size) - 0.5f,((float)j/ size) - 0.5f},
				{ i % 2, j % 2, 1.0f }
				});
		}
	}

	for (int i = 0; i < size-1; i++)
	{
		for (int j = 0; j < size-1; j++)
		{
			int currIndex = i + j * size;
			indices.push_back(currIndex);
			indices.push_back(currIndex + size);
			indices.push_back(currIndex + size + 1);
			indices.push_back(currIndex);
			indices.push_back(currIndex + size + 1);
			indices.push_back(currIndex + 1);
		}
	}

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