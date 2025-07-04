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

	//Получаем все потоки которые есть у видеокарты
	uint32_t CountQueue = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &CountQueue, nullptr);
	vector<VkQueueFamilyProperties> LocalQueue(CountQueue);
	vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &CountQueue, LocalQueue.data());

	for (int i = 0; i < LocalQueue.size(); i++) 
	{
		VkBool32 ValidSurfaceSupport = false;
		//Если определённый поток поддерживает вывод на Surface
		vkGetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice, i, Surface, &ValidSurfaceSupport);
		if (ValidSurfaceSupport) 
		{
			//То записываем его
			PresentQueue = i;
		}

		//Если определённый поток является потоком для графики
		VkQueueFamilyProperties Q = LocalQueue[i];
		if (Q.queueFlags & VK_QUEUE_GRAPHICS_BIT) 
		{
			//То записываем его
			GraphicsQueue = i;
			break;
		}
	}

	//Создание вектора для хранения информации о потоках
	vector<VkDeviceQueueCreateInfo> QueueInfos;
	//Создаём массив для хранения уникальных потоков
	set<uint32_t> UnQueue = {GraphicsQueue, PresentQueue};
	
	float QueuePriorities = 1.0f;
	for (const auto LocalQueue : UnQueue) 
	{
		//Создаём информацию о потоке
		VkDeviceQueueCreateInfo LocalInfo = {};
		LocalInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		LocalInfo.queueCount = 1; //Кол-во потоков
		LocalInfo.pQueuePriorities = &QueuePriorities; //Приоритет потока
		LocalInfo.queueFamilyIndex = LocalQueue; //Сам поток

		QueueInfos.push_back(LocalInfo);
	}


	VkDeviceCreateInfo DeviceInfo = {};
	DeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	DeviceInfo.enabledExtensionCount = static_cast<uint32_t>(Extensions.size()); //Кол-во Extensions
	DeviceInfo.ppEnabledExtensionNames = Extensions.data(); //Сами Extensions
	DeviceInfo.queueCreateInfoCount = static_cast<uint32_t>(QueueInfos.size()); //Кол-во потоков
	DeviceInfo.pQueueCreateInfos = QueueInfos.data(); //Сами потоки

	vkCreateDevice(PhysicalDevice, &DeviceInfo, nullptr, &Device);
}

void VkMain::VkSwapchainInitialization()
{
	//Создаём переменную для хранения режима отрисовки холстов
	VkPresentModeKHR PresentMode = VK_PRESENT_MODE_FIFO_KHR;
	uint32_t CountPresentMode = 0;
	//Получаем все режимы отрисовки холстов, которые есть у видеокарты
	vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice, Surface, &CountPresentMode, nullptr);
	vector<VkPresentModeKHR> LocalPresentMode(CountPresentMode);
	vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice, Surface, &CountPresentMode, LocalPresentMode.data());

	//Создаём переменную для хранения формата цвета и типа цвета
	VkSurfaceFormatKHR Format = {};
	uint32_t CountFormat = 0;
	//Получаем все форматы и типы цветов, которые есть у видеокарты
	vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &CountFormat, nullptr);
	vector<VkSurfaceFormatKHR> LocalFormat(CountFormat);
	vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &CountFormat, LocalFormat.data());

	for (VkPresentModeKHR AvaiblePresentMode : LocalPresentMode) 
	{
		//Если у видеокарты есть режим отрисовки холстов: VK_PRESENT_MODE_MAILBOX_KHR
		if (AvaiblePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) 
		{
			//То записываем этот режим
			PresentMode = AvaiblePresentMode;
			break;
		}
	}

	for (VkSurfaceFormatKHR AvaibleFormat : LocalFormat) 
	{
		//Если у видеокарты есть: тип цвета и формат цвета которые нам нужны
		if (AvaibleFormat.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR && AvaibleFormat.format == VK_FORMAT_R8G8B8A8_SRGB) 
		{
			//То записываем этот формат
			Format = AvaibleFormat;
			break;
		}
	}

	//Создание переменной для параметров холстов
	VkSurfaceCapabilitiesKHR Capabilities = {};
	//Получаем все параметры для холстов, которые есть у видеокарты
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(PhysicalDevice, Surface, &Capabilities);

	//Создаём переменную для хранения размера холстов
	VkExtent2D Size = Capabilities.currentExtent;
	//Создаём переменную с кол-во холстов(+1 нужно для того, чтоб создать ещё один холст. Тк у нас 2 потока)
	uint32_t CountImage = Capabilities.minImageCount + 1;

	//Создаём информацию про Swapchain
	VkSwapchainCreateInfoKHR SwapchainInfo = {};
	SwapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	SwapchainInfo.surface = Surface; //Задаём Surface
	SwapchainInfo.clipped = VK_TRUE; //Объекты которые вышли за пределы камеры отрисовываться не будут
	SwapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; //Холсты используются для передачи цветов
	SwapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; //Холсты не прозрачные
	SwapchainInfo.imageArrayLayers = 1; //1 слой
	SwapchainInfo.oldSwapchain = VK_NULL_HANDLE; //Старый Swapchain
	SwapchainInfo.presentMode = PresentMode; //Режим отрисовки
	SwapchainInfo.imageColorSpace = Format.colorSpace; //Тип цвета
	SwapchainInfo.imageFormat = Format.format; //Формат цвета
	SwapchainInfo.imageExtent = Size; //Размер холста
	SwapchainInfo.minImageCount = CountImage; //Кол-во холстов
	SwapchainInfo.preTransform = Capabilities.currentTransform; //Позиция, вращения, размер холста

	//Массив с потоками
	uint32_t Queue[] = { GraphicsQueue, PresentQueue };
	if (GraphicsQueue != PresentQueue) 
	{
		//Если потоки за отрисовку и за создания графики отличаются, то:
		//Потоки/Холсты могут между собой передавать информацию
		SwapchainInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		//2 потока
		SwapchainInfo.queueFamilyIndexCount = 2;
		//Сами потоки
		SwapchainInfo.pQueueFamilyIndices = Queue;
	}
	else
	{
		//Если они одинаковы, то они не могут передавать между собой информацию
		SwapchainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}

	vkCreateSwapchainKHR(Device, &SwapchainInfo, nullptr, &Swapchain);

}

void VkMain::VkImageViewInitialization()
{
	//Получаем формат для холстов
	VkFormat LocalFormat = Format.format;

	uint32_t CountImage = 0;
	//Получаем все холсты из Swapchain
	vkGetSwapchainImagesKHR(Device, Swapchain, &CountImage, nullptr);
	vector<VkImage> LocalImage(CountImage);
	vkGetSwapchainImagesKHR(Device, Swapchain, &CountImage, LocalImage.data());

	//Создаём вектор для хранения всех VkImageView
	vector<VkImageView> ImageView(LocalImage.size());
	for (int i = 0; i<LocalImage.size(); i++) 
	{
		//Создаём переменную для хранения информации о ImageView
		VkImageViewCreateInfo ImageViewInfo = {};
		ImageViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		//Привязываем ImageView к Image
		ImageViewInfo.image = LocalImage[i];
		//Указываем тип хослта 
		ImageViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		//Указываем формат цвета у холста
		ImageViewInfo.format = LocalFormat;
		//Указываем, что каждый элемент rgba равен своему цвету
		ImageViewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		//Указываем с каким типом холстов мы работаем
		ImageViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		//Указываем холст с которого нужно начать отрисовку
		ImageViewInfo.subresourceRange.baseArrayLayer = 0;
		//Указываем какой холст мы используем
		ImageViewInfo.subresourceRange.baseMipLevel = 0;
		//Указываем кол-во холстов
		ImageViewInfo.subresourceRange.levelCount = 1;

		//Создаём ImageView для каждого Image по индексу i
		vkCreateImageView(Device, &ImageViewInfo, nullptr, &ImageView[i]);
	}
}

void VkMain::VkRenderPassInitialization() 
{
	//Создание переменной для привязки
	VkAttachmentDescription Attachment = {};
	Attachment.format = Format.format; //Формат
	Attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR; //Отчистить буфер перед рендером
	Attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE; //Сохранить буфер в памяти после рендера
	Attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE; //Трафарет
	Attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE; //Трафарет
	Attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED; //Состояние изображения до рендера: неизвестно
	Attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR; //Состояние изображения после рендера: можно показывать на экран
	Attachment.samples = VK_SAMPLE_COUNT_1_BIT; //MultiSample

	//Создание переменной ссылки на наш Attachment
	VkAttachmentReference AttachmentReference = {};
	AttachmentReference.attachment = 0; //Индекс Attachment
	AttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL; //Изображение используется для прикрепления цвета

	//Создание подзадачи для RenderPass
	VkSubpassDescription Subpass = {};
	Subpass.colorAttachmentCount = 1; //Кол-во Attachment
	Subpass.pColorAttachments = &AttachmentReference; //Ссылка на Attachment
	Subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS; //Режим конвеера: графический

	//Создание информации о RenderPass
	VkRenderPassCreateInfo RenderPassInfo = {};
	RenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	RenderPassInfo.attachmentCount = 1; //Кол-во Attachment
	RenderPassInfo.pAttachments = &Attachment; //Сам Attachment
	RenderPassInfo.subpassCount = 1; //Кол-во подзадач
	RenderPassInfo.pSubpasses = &Subpass; //Сама подзадача


	
	//Создание RenderPass
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