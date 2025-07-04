#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <set>
#include <optional>

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

/**
	Struct that holds the index to the device's queue families
*/
struct QueueFamilyIndices
{
	/*
	*	Each device has a list of supported queues. Family Indices
	*	saves the index if the list corresponding to each queue.
	*/ 
	std::optional<uint32_t> graphicsFamily;	//Availavility of graphics queue
	std::optional<uint32_t> presentFamily;	//Availability of presentation family (can draw to a screen/window)

	/*
	It is considered complete if it has all the family queues needed.
	*/ 
	bool isComplete()
	{
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

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
	VkDevice device;
	VkQueue graphicsQueue;

	VkSurfaceKHR surface;
	VkQueue presentQueue;

	void initWindow();
	
	void initVulkan();

	void createInstance();

	void mainLoop();
	void cleanup();

	void pickPhysicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);
	void createLogicalDevice();

	void createSurface();

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

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

