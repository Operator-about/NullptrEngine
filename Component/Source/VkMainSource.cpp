#include<VkMainComponent.h>

void VkMain::VkInitialization(GLFWwindow* Window) 
{
	VkInstanceInitialization();

	VkSurfaceInitialization(Window);

	VkPhysicalDeviceInitialization();

	VkLogicalDeviceInitialization();

	VkSwapchainInitialization();
	
	VkImageViewInitialization();

	VkRenderPassInitialization();

	VkShaderInitialization("Shader/Vert.spv","Shader/Frag.spv");

	VkGraphicsPipelineInitialization();
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

	//�������� ��� ������ ������� ���� � ����������
	uint32_t CountQueue = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &CountQueue, nullptr);
	vector<VkQueueFamilyProperties> LocalQueue(CountQueue);
	vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &CountQueue, LocalQueue.data());

	for (int i = 0; i < LocalQueue.size(); i++) 
	{
		VkBool32 ValidSurfaceSupport = false;
		//���� ����������� ����� ������������ ����� �� Surface
		vkGetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice, i, Surface, &ValidSurfaceSupport);
		if (ValidSurfaceSupport) 
		{
			//�� ���������� ���
			PresentQueue = i;
		}

		//���� ����������� ����� �������� ������� ��� �������
		VkQueueFamilyProperties Q = LocalQueue[i];
		if (Q.queueFlags & VK_QUEUE_GRAPHICS_BIT) 
		{
			//�� ���������� ���
			GraphicsQueue = i;
			break;
		}
	}

	//�������� ������� ��� �������� ���������� � �������
	vector<VkDeviceQueueCreateInfo> QueueInfos;
	//������ ������ ��� �������� ���������� �������
	set<uint32_t> UnQueue = {GraphicsQueue, PresentQueue};
	
	float QueuePriorities = 1.0f;
	for (const auto LocalQueue : UnQueue) 
	{
		//������ ���������� � ������
		VkDeviceQueueCreateInfo LocalInfo = {};
		LocalInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		LocalInfo.queueCount = 1; //���-�� �������
		LocalInfo.pQueuePriorities = &QueuePriorities; //��������� ������
		LocalInfo.queueFamilyIndex = LocalQueue; //��� �����

		QueueInfos.push_back(LocalInfo);
	}


	VkDeviceCreateInfo DeviceInfo = {};
	DeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	DeviceInfo.enabledExtensionCount = static_cast<uint32_t>(Extensions.size()); //���-�� Extensions
	DeviceInfo.ppEnabledExtensionNames = Extensions.data(); //���� Extensions
	DeviceInfo.queueCreateInfoCount = static_cast<uint32_t>(QueueInfos.size()); //���-�� �������
	DeviceInfo.pQueueCreateInfos = QueueInfos.data(); //���� ������

	vkCreateDevice(PhysicalDevice, &DeviceInfo, nullptr, &Device);
}

void VkMain::VkSwapchainInitialization()
{
	//������ ���������� ��� �������� ������ ��������� �������
	VkPresentModeKHR PresentMode = VK_PRESENT_MODE_FIFO_KHR;
	uint32_t CountPresentMode = 0;
	//�������� ��� ������ ��������� �������, ������� ���� � ����������
	vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice, Surface, &CountPresentMode, nullptr);
	vector<VkPresentModeKHR> LocalPresentMode(CountPresentMode);
	vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice, Surface, &CountPresentMode, LocalPresentMode.data());

	//������ ���������� ��� �������� ������� ����� � ���� �����
	VkSurfaceFormatKHR Format = {};
	uint32_t CountFormat = 0;
	//�������� ��� ������� � ���� ������, ������� ���� � ����������
	vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &CountFormat, nullptr);
	vector<VkSurfaceFormatKHR> LocalFormat(CountFormat);
	vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &CountFormat, LocalFormat.data());

	for (VkPresentModeKHR AvaiblePresentMode : LocalPresentMode) 
	{
		//���� � ���������� ���� ����� ��������� �������: VK_PRESENT_MODE_MAILBOX_KHR
		if (AvaiblePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) 
		{
			//�� ���������� ���� �����
			PresentMode = AvaiblePresentMode;
			break;
		}
	}

	for (VkSurfaceFormatKHR AvaibleFormat : LocalFormat) 
	{
		//���� � ���������� ����: ��� ����� � ������ ����� ������� ��� �����
		if (AvaibleFormat.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR && AvaibleFormat.format == VK_FORMAT_R8G8B8A8_SRGB) 
		{
			//�� ���������� ���� ������
			Format = AvaibleFormat;
			break;
		}
	}

	//�������� ���������� ��� ���������� �������
	VkSurfaceCapabilitiesKHR Capabilities = {};
	//�������� ��� ��������� ��� �������, ������� ���� � ����������
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(PhysicalDevice, Surface, &Capabilities);

	//������ ���������� ��� �������� ������� �������
	VkExtent2D Size = Capabilities.currentExtent;
	//������ ���������� � ���-�� �������(+1 ����� ��� ����, ���� ������� ��� ���� �����. �� � ��� 2 ������)
	uint32_t CountImage = Capabilities.minImageCount + 1;

	//������ ���������� ��� Swapchain
	VkSwapchainCreateInfoKHR SwapchainInfo = {};
	SwapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	SwapchainInfo.surface = Surface; //����� Surface
	SwapchainInfo.clipped = VK_TRUE; //������� ������� ����� �� ������� ������ �������������� �� �����
	SwapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; //������ ������������ ��� �������� ������
	SwapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; //������ �� ����������
	SwapchainInfo.imageArrayLayers = 1; //1 ����
	SwapchainInfo.oldSwapchain = VK_NULL_HANDLE; //������ Swapchain
	SwapchainInfo.presentMode = PresentMode; //����� ���������
	SwapchainInfo.imageColorSpace = Format.colorSpace; //��� �����
	SwapchainInfo.imageFormat = Format.format; //������ �����
	SwapchainInfo.imageExtent = Size; //������ ������
	SwapchainInfo.minImageCount = CountImage; //���-�� �������
	SwapchainInfo.preTransform = Capabilities.currentTransform; //�������, ��������, ������ ������

	//������ � ��������
	uint32_t Queue[] = { GraphicsQueue, PresentQueue };
	if (GraphicsQueue != PresentQueue) 
	{
		//���� ������ �� ��������� � �� �������� ������� ����������, ��:
		//������/������ ����� ����� ����� ���������� ����������
		SwapchainInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		//2 ������
		SwapchainInfo.queueFamilyIndexCount = 2;
		//���� ������
		SwapchainInfo.pQueueFamilyIndices = Queue;
	}
	else
	{
		//���� ��� ���������, �� ��� �� ����� ���������� ����� ����� ����������
		SwapchainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}

	vkCreateSwapchainKHR(Device, &SwapchainInfo, nullptr, &Swapchain);

}

void VkMain::VkImageViewInitialization()
{
	//�������� ������ ��� �������
	VkFormat LocalFormat = Format.format;

	uint32_t CountImage = 0;
	//�������� ��� ������ �� Swapchain
	vkGetSwapchainImagesKHR(Device, Swapchain, &CountImage, nullptr);
	vector<VkImage> LocalImage(CountImage);
	vkGetSwapchainImagesKHR(Device, Swapchain, &CountImage, LocalImage.data());

	//������ ������ ��� �������� ���� VkImageView
	vector<VkImageView> ImageView(LocalImage.size());
	for (int i = 0; i<LocalImage.size(); i++) 
	{
		//������ ���������� ��� �������� ���������� � ImageView
		VkImageViewCreateInfo ImageViewInfo = {};
		ImageViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		//����������� ImageView � Image
		ImageViewInfo.image = LocalImage[i];
		//��������� ��� ������ 
		ImageViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		//��������� ������ ����� � ������
		ImageViewInfo.format = LocalFormat;
		//���������, ��� ������ ������� rgba ����� ������ �����
		ImageViewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		//��������� � ����� ����� ������� �� ��������
		ImageViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		//��������� ����� � �������� ����� ������ ���������
		ImageViewInfo.subresourceRange.baseArrayLayer = 0;
		//��������� ����� ����� �� ����������
		ImageViewInfo.subresourceRange.baseMipLevel = 0;
		//��������� ���-�� �������
		ImageViewInfo.subresourceRange.levelCount = 1;

		//������ ImageView ��� ������� Image �� ������� i
		vkCreateImageView(Device, &ImageViewInfo, nullptr, &ImageView[i]);
	}
}

void VkMain::VkRenderPassInitialization() 
{
	//�������� ���������� ��� ��������
	VkAttachmentDescription Attachment = {};
	Attachment.format = Format.format; //������
	Attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR; //��������� ����� ����� ��������
	Attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE; //��������� ����� � ������ ����� �������
	Attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE; //��������
	Attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE; //��������
	Attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED; //��������� ����������� �� �������: ����������
	Attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR; //��������� ����������� ����� �������: ����� ���������� �� �����
	Attachment.samples = VK_SAMPLE_COUNT_1_BIT; //MultiSample

	//�������� ���������� ������ �� ��� Attachment
	VkAttachmentReference AttachmentReference = {};
	AttachmentReference.attachment = 0; //������ Attachment
	AttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL; //����������� ������������ ��� ������������ �����

	//�������� ��������� ��� RenderPass
	VkSubpassDescription Subpass = {};
	Subpass.colorAttachmentCount = 1; //���-�� Attachment
	Subpass.pColorAttachments = &AttachmentReference; //������ �� Attachment
	Subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS; //����� ��������: �����������

	//�������� ���������� � RenderPass
	VkRenderPassCreateInfo RenderPassInfo = {};
	RenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	RenderPassInfo.attachmentCount = 1; //���-�� Attachment
	RenderPassInfo.pAttachments = &Attachment; //��� Attachment
	RenderPassInfo.subpassCount = 1; //���-�� ��������
	RenderPassInfo.pSubpasses = &Subpass; //���� ���������


	
	//�������� RenderPass
	vkCreateRenderPass(Device, &RenderPassInfo, nullptr, &RenderPass);
}

void VkMain::VkShaderInitialization(string VertexShader, string FragmentShader)
{
	vector<string> VertShader = LoadFile(VertexShader);
	vector<string> FragShader = LoadFile(FragmentShader);

	VkShaderModuleCreateInfo ShaderVertexModuleInfo = {};
	ShaderVertexModuleInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	ShaderVertexModuleInfo.codeSize = VertShader.size();
	ShaderVertexModuleInfo.pCode = reinterpret_cast<const uint32_t*>(VertShader.data());

	VkShaderModuleCreateInfo ShaderFragmentModuleInfo = {};
	ShaderFragmentModuleInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	ShaderFragmentModuleInfo.codeSize = FragShader.size();
	ShaderFragmentModuleInfo.pCode = reinterpret_cast<const uint32_t*>(FragShader.data());

	
	vkCreateShaderModule(Device, &ShaderVertexModuleInfo, nullptr, &ShaderVertexModule);
	vkCreateShaderModule(Device, &ShaderFragmentModuleInfo, nullptr, &ShaderFragmentModule);
}

void VkMain::VkGraphicsPipelineInitialization()
{
	VkPipelineShaderStageCreateInfo VertexShaderStage = {};
	VertexShaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	VertexShaderStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
	VertexShaderStage.module = ShaderVertexModule;
	VertexShaderStage.pName = "main";

	VkPipelineShaderStageCreateInfo FragmentShaderStage = {};
	FragmentShaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	FragmentShaderStage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	FragmentShaderStage.module = ShaderFragmentModule;
	FragmentShaderStage.pName = "main";

	VkPipelineShaderStageCreateInfo ShaderStage[] = {VertexShaderStage, FragmentShaderStage};

	VkGraphicsPipelineCreateInfo GraphicsPipelineInfo = {};
	GraphicsPipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	GraphicsPipelineInfo.renderPass = RenderPass;
	GraphicsPipelineInfo.stageCount = 2;
	GraphicsPipelineInfo.pStages = ShaderStage;

	VkPipeline GraphicsPipeline = {};
	vkCreateGraphicsPipelines(Device, VK_NULL_HANDLE, 2, &GraphicsPipelineInfo, nullptr, &GraphicsPipeline);

}