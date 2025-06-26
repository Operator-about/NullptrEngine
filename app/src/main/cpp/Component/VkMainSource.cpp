#include"VkMainComponent.h"

void VkMain::VkInitialization(ANativeWindow* Window)
{

    VkInstance Instance = {};
    VkInstanceCreateInfo Info = {};
    VkInstanceInitialization(Instance, Info);

    VkSurfaceKHR Surface = {};
    VkAndroidSurfaceCreateInfoKHR SurfaceInfo = {};
    VkSurfaceInitialization(Instance, Surface, SurfaceInfo, Window);

    VkPhysicalDevice PhysicalDevice = {};
    VkPhysicalDeviceInitialization(Instance, PhysicalDevice);

    VkDevice Device = {};
    VkLogicalDeviceInitialization(Instance, PhysicalDevice, Surface, Device);


}



void VkMain::VkInstanceInitialization(VkInstance &Instance, VkInstanceCreateInfo &Info)
{
    vector<const char*> Extensions;
    Extensions.push_back("VK_KHR_SURFACE");
    Extensions.push_back("VK_KHR_android_surface");

    VkApplicationInfo App = {};
    App.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    App.applicationVersion = VK_MAKE_VERSION(1,0,0);
    App.pApplicationName = "NullptrEngine";
    App.pEngineName = nullptr;
    App.engineVersion = VK_MAKE_VERSION(1,0,0);
    App.apiVersion = VK_VERSION_1_3;

    Info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    Info.pApplicationInfo = &App;
//    Info.enabledExtensionCount = (uint32_t)Extensions.size();
//    Info.ppEnabledExtensionNames = Extensions.data();
    Info.enabledLayerCount = 0;
    Info.pNext = nullptr;

    vkCreateInstance(&Info, nullptr, &Instance);
}

void VkMain::VkPhysicalDeviceInitialization(VkInstance Instance, VkPhysicalDevice &PhysicalDevice)
{
    uint32_t PhysicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, nullptr);
    vector<VkPhysicalDevice> LocalDevice(PhysicalDeviceCount);
    vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, LocalDevice.data());

    PhysicalDevice = LocalDevice.data()[0];
}


void VkMain::VkLogicalDeviceInitialization(VkInstance Instance, VkPhysicalDevice PhysicalDevice, VkSurfaceKHR Surface, VkDevice &Device)
{

    uint32_t QueueCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueCount, nullptr);
    vector<VkQueueFamilyProperties> LocalQueue(QueueCount);
    vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueCount, LocalQueue.data());

    uint32_t QueueGraphicsIndex = 0;
    uint32_t QueuePresentIndex = 0;

    for(uint32_t i = 0; i<LocalQueue.size(); i++)
    {
        VkBool32 SurfaceValid = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice, i, Surface, &SurfaceValid);
        if(SurfaceValid == true)
        {
            QueuePresentIndex = i;
        }

        VkQueueFamilyProperties LocalPropQueue = LocalQueue[i];
        if(LocalPropQueue.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            QueueGraphicsIndex = i;
            break;
        }
    }

    vector<VkDeviceQueueCreateInfo> QueueInfos = {};
    set<uint32_t> UnQueue = {QueueGraphicsIndex, QueuePresentIndex};

    float QueuePrority = 1.0f;
    for(const uint32_t LocalQueue : UnQueue)
    {
        VkDeviceQueueCreateInfo LocalInfoQueue = {};
        LocalInfoQueue.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        LocalInfoQueue.queueCount = 1;
        LocalInfoQueue.pQueuePriorities = &QueuePrority;
        LocalInfoQueue.queueFamilyIndex = LocalQueue;
        QueueInfos.push_back(LocalInfoQueue);
    }

    VkDeviceCreateInfo DeviceInfo = {};
    DeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    DeviceInfo.enabledExtensionCount = 0;
    DeviceInfo.queueCreateInfoCount = (uint32_t)QueueInfos.size();
    DeviceInfo.pQueueCreateInfos = QueueInfos.data();


    vkCreateDevice(PhysicalDevice, &DeviceInfo, nullptr, &Device);


}

void VkMain::VkSurfaceInitialization(VkInstance Instance, VkSurfaceKHR &Surface, VkAndroidSurfaceCreateInfoKHR &SurfaceInfo, ANativeWindow* Window)
{
    SurfaceInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    SurfaceInfo.window = Window;
    vkCreateAndroidSurfaceKHR(Instance, &SurfaceInfo , nullptr, &Surface);
}

void VkMain::VkSwapchainInitialization(VkDevice Device, VkSwapchainCreateInfoKHR &SwapchainInfo, VkSwapchainKHR &Swapchain)
{

    vkCreateSwapchainKHR(Device, &SwapchainInfo, nullptr, &Swapchain);

}


