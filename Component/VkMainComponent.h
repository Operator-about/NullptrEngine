#include<iostream>
#include<vector>
#include<set>
#include<vulkan/vulkan.h>
#include<GLFW/glfw3.h>
using namespace std;

class VkMain
{

public:
	void VkInitialization(GLFWwindow* Window);

private:
	VkInstance Instance;
	VkPhysicalDevice PhysicalDevice;
	VkDevice Device;
	uint32_t GraphicsQueue = 0, PresentQueue = 0;
	VkSwapchainKHR Swapchain;
	VkSurfaceKHR Surface;

	void VkInstanceInitialization();
	void VkPhysicalDeviceInitialization();
	void VkLogicalDeviceInitialization();
	void VkSurfaceInitialization(GLFWwindow* Window);
	void VkSwapchainInitialization();
};
