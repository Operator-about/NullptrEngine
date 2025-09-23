#include"StartupNullptrEngineComponent.h"

StartupNullptrEngine::StartupNullptrEngine(ANativeWindow* Window)
{
    this->StartupNullptrEngineInstance();
    this->StartupNullptrEnginePhysicalDevice();
    this->StartupNullptrEngineSurface(Window);
    this->StartupNullptrEngineDevice();


}

void StartupNullptrEngine::StartupNullptrEngineInstance()
{
    vector<const char*> Extension;
    vector<const char*> Layers;

    VkApplicationInfo AppInfo = {
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pApplicationName = "NullptrEngine",
            .applicationVersion = VK_MAKE_VERSION(1,0,0),
            .pEngineName = nullptr,
            .engineVersion = VK_MAKE_VERSION(1,0,0),
            .apiVersion = VK_API_VERSION_1_3
    };

    VkInstanceCreateInfo InstanceInfo = {
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pApplicationInfo = &AppInfo
    };

    uint32_t ExCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &ExCount, nullptr);
    vector<VkExtensionProperties> ExtensionsProperties(ExCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &ExCount, ExtensionsProperties.data());

    for(int i = 0; i < ExtensionsProperties.size(); i++)
    {
        Extension.push_back(ExtensionsProperties[i].extensionName);
    }

    uint32_t LayerCount = 0;
    vkEnumerateInstanceLayerProperties(&LayerCount, nullptr);
    vector<VkLayerProperties> LayersProperties(LayerCount);
    vkEnumerateInstanceLayerProperties(&LayerCount, LayersProperties.data());

    for(int i = 0; i < LayersProperties.size(); i++)
    {
        Layers.push_back(LayersProperties[i].layerName);
    }

//    InstanceInfo.enabledExtensionCount = static_cast<uint32_t>(Extension.size());
//    InstanceInfo.ppEnabledExtensionNames = Extension.data();
    InstanceInfo.enabledLayerCount = static_cast<uint32_t>(LayersProperties.size());
    InstanceInfo.ppEnabledLayerNames = Layers.data();

    vkCreateInstance(&InstanceInfo, nullptr, &Instance);
}

void StartupNullptrEngine::StartupNullptrEnginePhysicalDevice()
{
    uint32_t PhysicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, nullptr);
    vector<VkPhysicalDevice> PhysicalDevices(PhysicalDeviceCount);
    vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, PhysicalDevices.data());

    PhysicalDevice = PhysicalDevices.data()[0];
    vkGetPhysicalDeviceFeatures(PhysicalDevice, &PhysicalDeviceFeatures);
}

void StartupNullptrEngine::StartupNullptrEngineSurface(ANativeWindow* Window)
{
    VkAndroidSurfaceCreateInfoKHR SurfaceInfo = {
            .sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
            .pNext = nullptr,
            .flags = 0,
            .window = Window
    };
    vkCreateAndroidSurfaceKHR(Instance, &SurfaceInfo, nullptr, &Surface);
}

void StartupNullptrEngine::StartupNullptrEngineDevice()
{
    uint32_t QueueCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueCount, nullptr);
    vector<VkQueueFamilyProperties> QueueProperties(QueueCount);
    vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueCount, QueueProperties.data());

    for(int i = 0; i < QueueProperties.size(); i++)
    {
        VkBool32 Valid = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice, i, Surface, &Valid);
        if(Valid == true)
        {
            PresentQueueFamily = i;
        }

        VkQueueFamilyProperties Q = QueueProperties[i];
        if(Q.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            GraphicsQueueFamily = i;
            break;
        }
    }

    vector<VkDeviceQueueCreateInfo> QueueInfos;
    set<uint32_t> UnQueue = {GraphicsQueueFamily, PresentQueueFamily};

    float Priorities = 1.0f;

    for(auto LocalQueue : UnQueue)
    {
        VkDeviceQueueCreateInfo QueueInfo = {
                .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                .queueFamilyIndex = LocalQueue,
                .queueCount = 1,
                .pQueuePriorities = &Priorities
        };

        QueueInfos.push_back(QueueInfo);
    }

    VkDeviceCreateInfo DeviceInfo = {
            .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
            .queueCreateInfoCount = static_cast<uint32_t>(QueueInfos.size()),
            .pQueueCreateInfos = QueueInfos.data()
    };


    uint32_t LQueueFamilyIndex[] = {GraphicsQueueFamily, PresentQueueFamily};
    QueueFamilyIndex = LQueueFamilyIndex;
    vkCreateDevice(PhysicalDevice, &DeviceInfo, nullptr, &Device);
}
