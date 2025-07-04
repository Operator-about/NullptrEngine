#include<iostream>
#include<vector>
#include<set>
#include<vulkan/vulkan.h>
#include<GLFW/glfw3.h>
#include<LoadFileComponents.h>
using namespace std;

class VkMain
{

public:

	void VkInitialization(GLFWwindow* Window);

private:
	VkInstance Instance = {};
	VkPhysicalDevice PhysicalDevice = {};
	VkDevice Device = {};
	uint32_t GraphicsQueue = 0, PresentQueue = 0;
	VkSwapchainKHR Swapchain = {};
	VkSurfaceKHR Surface = {};
	VkSurfaceFormatKHR Format = {};
	VkRenderPass RenderPass = {};
	VkShaderModule ShaderVertexModule = {};
	VkShaderModule ShaderFragmentModule = {};


	void VkInstanceInitialization();
	void VkPhysicalDeviceInitialization();
	void VkLogicalDeviceInitialization();
	void VkSurfaceInitialization(GLFWwindow* Window);
	void VkSwapchainInitialization();
	void VkImageViewInitialization();
	void VkRenderPassInitialization();
	void VkShaderInitialization(string VertexShader, string FragmentShader);
	void VkGraphicsPipelineInitialization();
};
