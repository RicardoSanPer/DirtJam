#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

extern const uint32_t WINDOW_WIDTH;
extern const uint32_t WINDOW_HEIGHT;

const std::vector<const char*> validationLayers =
{
	"VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

class VulkanApp
{
public:
	void run();

private:
	const char* const windowName = "DIRT JAM";
	SDL_Window* window;
	bool isRunning = false;
	
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	void initWindow();
	
	void initVulkan();
	void createInstance();

	void mainLoop();
	void cleanup();

	void pickPhysicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);

	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();
	
	void setupDebugMessenger();
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
		{
			std::cerr << "Validation Layer: " << pCallbackData->pMessage << std::endl;
			return VK_FALSE;
		};

	VkResult CreateDebugUtilsMessengerEXT(
		VkInstance instance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pDebugMessenger);

	void DestroyDebugUtilsMessengerEXT(
		VkInstance instance,
		VkDebugUtilsMessengerEXT debugMessenger,
		const VkAllocationCallbacks* pAllocator);

};

