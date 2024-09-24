#pragma once

#include <SDL2/SDL.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <SDL2/SDL_vulkan.h>
#include <fstream>
#include <set>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "global.hpp"

class VulkanApp
{
public:
	void run();

private:
	struct UniformBufferObject
	{
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};
	struct Vertex
	{
		glm::vec3 position;
	};
	// cube
	const std::vector<uint16_t> indices = {
		// Front face
		0, 1, 2, 2, 3, 0,
		// Back face
		4, 5, 6, 6, 7, 4,
		// Top face
		3, 2, 6, 6, 7, 3,
		// Bottom face
		0, 1, 5, 5, 4, 0,
		// Right face
		1, 5, 6, 6, 2, 1,
		// Left face
		0, 4, 7, 7, 3, 0};


	const std::vector<Vertex> vertices = {
		// Front face
		{{-0.5f, -0.5f, 0.5f}},
		{{0.5f, -0.5f, 0.5f}},
		{{0.5f, 0.5f, 0.5f}},
		{{-0.5f, 0.5f, 0.5f}},
		// Back face
		{{-0.5f, -0.5f, -0.5f}},
		{{0.5f, -0.5f, -0.5f}},
		{{0.5f, 0.5f, -0.5f}},
		{{-0.5f, 0.5f, -0.5f}},
	};

	void initWindow();
	void initVulkan();
	void mainLoop();
	void cleanup();
	void createDescriptorPool();
	void createDescriptorSetLayout();
	void createUniformBuffer();
	void updateUniformBuffer();
	void processInput();
	void createDescriptorSets();
	void createTextureImage();
	void createTextureImageView();
	void createTextureSampler();
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	void createVertexBuffer();
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	void createIndexBuffer();
	void createUniformBuffers();
	VkShaderModule createShaderModule(const std::vector<char> &code);
	void createFramebuffers();
	void createCommandBuffers();
	void createSyncObjects();
	void updateUniformBuffer(uint32_t currentImage);
	void drawFrame();
	void recreateSwapChain();
	void cleanupSwapChain();
	void createInstance();
	void setupDebugMessenger();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createRenderPass();
	void createGraphicsPipeline();
	bool isDeviceSuitable(VkPhysicalDevice device);

	void createSwapChain();
	bool checkValidationLayerSupport();

	void createImageViews();

	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
	SDL_Window *window;
	VkInstance instance;
	VkSurfaceKHR surface;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkCommandPoolCreateInfo poolInfo = {};
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	bool framebufferResized = false;
	size_t currentFrame = 0;
	VkBuffer uniformBuffer;

	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	VkDescriptorSetLayout descriptorSetLayout;
	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;
	const std::vector<const char *> validationLayers = {
		"VK_LAYER_KHRONOS_validation"};

	const std::vector<const char *> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME};
	glm::vec3 rotation = glm::vec3(0.0f);

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif
};
