#include"VkMainComponent.h"

void VkMain::VkInitialization()
{

    VkExtensionsInitialization();
    VkInstanceInitialization();
    VkPhysicalDevicesInitialization();
    //VkLogicalDevicesInitialization();

};

void VkMain::VkExtensionsInitialization()
{
    Extensions.push_back("VK_KHR_SURFACE");
    Extensions.push_back("VK_KHR_android_surface");
}

void VkMain::VkInstanceInitialization()
{
    VkExtensionsInitialization();
    VkApplicationInfo App = {};
    App.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    App.applicationVersion = VK_MAKE_VERSION(1,0,0);
    App.pApplicationName = "NullptrEngine";
    App.pEngineName = nullptr;
    App.engineVersion = VK_MAKE_VERSION(1,0,0);
    App.apiVersion = VK_VERSION_1_3;

    Info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    Info.pApplicationInfo = &App;
    Info.enabledExtensionCount = static_cast<uint32_t>(Extensions.size());
    Info.ppEnabledExtensionNames = Extensions.data();
    Info.enabledLayerCount = 0;
    Info.pNext = nullptr;

    vkCreateInstance(&Info, nullptr, &Instance);
}

void VkMain::VkPhysicalDevicesInitialization()
{
    uint32_t PhysicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, nullptr);
    vector<VkPhysicalDevice> LocalDevice(PhysicalDeviceCount);
    vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, LocalDevice.data());

    for(const VkPhysicalDevice LocalDeviceLoop : LocalDevice)
    {
        PhysicalDevice = LocalDeviceLoop;
    }
}

void VkMain::VkLogicalDevicesInitialization()
{
    uint32_t CountQueue = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &CountQueue, nullptr);
    vector<VkQueueFamilyProperties> QueueProp(CountQueue);
    vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &CountQueue, QueueProp.data());

    uint32_t QueueGraphicsIndex = 0;
    uint32_t QueuePresentIndex = 0;

    for(int i = 0; i<QueueProp.size();i++)
    {
        VkBool32 PresentValid = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice, i, Surface, &PresentValid);
        if(PresentValid)
        {
            QueuePresentIndex = i;
        }

        VkQueueFamilyProperties LocalQueueProp = QueueProp[i];
        if(LocalQueueProp.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            QueueGraphicsIndex = i;
            break;
        }
    }

    vector<VkDeviceQueueCreateInfo> QueueInfos;
    set<uint32_t> UnQueue = {QueueGraphicsIndex, QueuePresentIndex};

    for(const uint32_t LocalQueue : UnQueue)
    {
        VkDeviceQueueCreateInfo QueueInfo = {};
        QueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        QueueInfo.queueCount = 1;
        QueueInfo.queueFamilyIndex = LocalQueue; //Если, что-то пойдёт не так, то надо поставить QueueGraphicsIndex

        QueueInfos.push_back(QueueInfo);
    }

    VkDeviceCreateInfo DeviceInfo = {};
    DeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    DeviceInfo.enabledExtensionCount = 0;
    DeviceInfo.queueCreateInfoCount = static_cast<uint32_t>(QueueInfos.size());
    DeviceInfo.pQueueCreateInfos = QueueInfos.data();

    VkDevice Device = {};
    vkCreateDevice(PhysicalDevice, &DeviceInfo, nullptr, &Device);
}

void VkMain::VKSurfaceInitialization()
{
    SurfaceInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    //.window = Window;

    vkCreateAndroidSurfaceKHR(Instance, &SurfaceInfo, nullptr, &Surface);
}
