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
#include <limits>
#include <algorithm>

#include <fstream>

extern const uint32_t WINDOW_WIDTH;
extern const uint32_t WINDOW_HEIGHT;

//Validation layers
const std::vector<const char*> validationLayers =
{
	"VK_LAYER_KHRONOS_validation"
};

/*
	List of required extensions
*/
const std::vector<const char*> deviceExtensions =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
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

/*
	Holds details of the details for the swap chain supported such as:
	Surface Capabilites: number of images in swap, width, height.
	Formats: pixel format, color space.
	Presentation modes.
*/
struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
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
	VkSwapchainKHR swapChain;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;

	VkPipelineLayout pipelineLayout;

	void initWindow();
	
	void initVulkan();
	void createInstance();

	void mainLoop();
	void cleanup();

	void pickPhysicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	void createLogicalDevice();

	void createSurface();
	void createSwapChain();
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	void createImageViews();

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	void createGraphicsPipeline();
	VkShaderModule createShaderModule(const std::vector<char>& code);


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

	static std::vector<char> readFile(const std::string& fileName);

};

