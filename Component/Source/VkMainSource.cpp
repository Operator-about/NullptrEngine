#include<VkMainComponent.h>

void VkMain::VkInitialization(GLFWwindow* Window) 
{
	VkInstanceInitialization();

	VkSurfaceInitialization(Window);

	VkPhysicalDeviceInitialization();

	VkLogicalDeviceInitialization();

	VkSwapchainInitialization();
}


void VkMain::VkInstanceInitialization() 
{
	uint32_t CountExtensions = 0;
	const char** ExtensionNames = glfwGetRequiredInstanceExtensions(&CountExtensions);
	vector<const char*> Extensions(ExtensionNames, ExtensionNames + CountExtensions);

	VkApplicationInfo AppInfo = {};
	AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	AppInfo.apiVersion = VK_API_VERSION_1_4;
	AppInfo.pEngineName = "No Engine";
	AppInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	AppInfo.pApplicationName = "NullptrEngine";
	AppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);

	VkInstanceCreateInfo Info = {};
	Info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	Info.pApplicationInfo = &AppInfo;
	Info.enabledExtensionCount = static_cast<uint32_t>(Extensions.size());
	Info.ppEnabledExtensionNames = Extensions.data();

	vkCreateInstance(&Info, nullptr, &Instance);
}

void VkMain::VkPhysicalDeviceInitialization()
{
	uint32_t CountPhysicalDevice = 0;
	vkEnumeratePhysicalDevices(Instance, &CountPhysicalDevice, nullptr);
	vector<VkPhysicalDevice> LocalPhysicalDevice(CountPhysicalDevice);
	vkEnumeratePhysicalDevices(Instance, &CountPhysicalDevice, LocalPhysicalDevice.data());

	PhysicalDevice = LocalPhysicalDevice.data()[0];
}

void VkMain::VkSurfaceInitialization(GLFWwindow* Window)
{
	glfwCreateWindowSurface(Instance, Window, nullptr, &Surface);
}

void VkMain::VkLogicalDeviceInitialization()
{
	vector<const char*> Extensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

	uint32_t CountQueue = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &CountQueue, nullptr);
	vector<VkQueueFamilyProperties> LocalQueue(CountQueue);
	vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &CountQueue, LocalQueue.data());

	cout << "Physical:" << PhysicalDevice << endl;
	cout << "Surface:" << Surface << endl;

	for (int i = 0; i < LocalQueue.size(); i++) 
	{
		VkBool32 ValidSurfaceSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice, i, Surface, &ValidSurfaceSupport);
		if (ValidSurfaceSupport) 
		{
			PresentQueue = i;
		}

		VkQueueFamilyProperties Q = LocalQueue[i];
		if (Q.queueFlags & VK_QUEUE_GRAPHICS_BIT) 
		{
			GraphicsQueue = i;
			break;
		}
	}

	vector<VkDeviceQueueCreateInfo> QueueInfos;
	set<uint32_t> UnQueue = {GraphicsQueue, PresentQueue};
	
	float QueuePriorities = 1.0f;
	for (const auto LocalQueue : UnQueue) 
	{
		VkDeviceQueueCreateInfo LocalInfo = {};
		LocalInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		LocalInfo.queueCount = 1;
		LocalInfo.pQueuePriorities = &QueuePriorities;
		LocalInfo.queueFamilyIndex = LocalQueue;

		QueueInfos.push_back(LocalInfo);
	}


	VkDeviceCreateInfo DeviceInfo = {};
	DeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	DeviceInfo.enabledExtensionCount = static_cast<uint32_t>(Extensions.size());
	DeviceInfo.ppEnabledExtensionNames = Extensions.data();
	DeviceInfo.queueCreateInfoCount = static_cast<uint32_t>(QueueInfos.size());
	DeviceInfo.pQueueCreateInfos = QueueInfos.data();

	vkCreateDevice(PhysicalDevice, &DeviceInfo, nullptr, &Device);
}

void VkMain::VkSwapchainInitialization()
{

	VkPresentModeKHR PresentMode = VK_PRESENT_MODE_FIFO_KHR;
	uint32_t CountPresentMode = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice, Surface, &CountPresentMode, nullptr);
	vector<VkPresentModeKHR> LocalPresentMode(CountPresentMode);
	vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice, Surface, &CountPresentMode, LocalPresentMode.data());

	VkSurfaceFormatKHR Format = {};
	uint32_t CountFormat = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &CountFormat, nullptr);
	vector<VkSurfaceFormatKHR> LocalFormat(CountFormat);
	vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &CountFormat, LocalFormat.data());

	for (VkPresentModeKHR AvaiblePresentMode : LocalPresentMode) 
	{
		if (AvaiblePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) 
		{
			PresentMode = AvaiblePresentMode;
			break;
		}
	}

	for (VkSurfaceFormatKHR AvaibleFormat : LocalFormat) 
	{
		if (AvaibleFormat.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR && AvaibleFormat.format == VK_FORMAT_R8G8B8A8_SRGB) 
		{
			Format = AvaibleFormat;
			break;
		}
	}

	VkSurfaceCapabilitiesKHR Capabilities = {};
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(PhysicalDevice, Surface, &Capabilities);

	VkExtent2D Size = Capabilities.currentExtent;
	uint32_t CountImage = Capabilities.minImageCount + 1;

	VkSwapchainCreateInfoKHR SwapchainInfo = {};
	SwapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	SwapchainInfo.surface = Surface;
	SwapchainInfo.clipped = VK_TRUE;
	SwapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	SwapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	SwapchainInfo.imageArrayLayers = 1;
	SwapchainInfo.oldSwapchain = VK_NULL_HANDLE;
	SwapchainInfo.presentMode = PresentMode;
	SwapchainInfo.imageColorSpace = Format.colorSpace;
	SwapchainInfo.imageFormat = Format.format;
	SwapchainInfo.imageExtent = Size;
	SwapchainInfo.minImageCount = CountImage;
	SwapchainInfo.preTransform = Capabilities.currentTransform;

	uint32_t Queue[] = { GraphicsQueue, PresentQueue };
	if (GraphicsQueue != PresentQueue) 
	{
		SwapchainInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		SwapchainInfo.queueFamilyIndexCount = 2;
		SwapchainInfo.pQueueFamilyIndices = Queue;
	}
	else
	{
		SwapchainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}

	vkCreateSwapchainKHR(Device, &SwapchainInfo, nullptr, &Swapchain);

}