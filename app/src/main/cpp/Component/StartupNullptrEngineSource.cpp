#include"StartupNullptrEngineComponent.h"

StartupNullptrEngine::StartupNullptrEngine()
{
    this->StartupNullptrEngineInstance();
}

void StartupNullptrEngine::StartupNullptrEngineInstance()
{
    vector<const char*> Extensions;
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

    VkInstance Instance = {};


    uint32_t ExCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &ExCount, nullptr);
    vector<VkExtensionProperties> ExtensionsProperties(ExCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &ExCount, ExtensionsProperties.data());

    for(int i = 0; i < ExtensionsProperties.size(); i++)
    {
        Extensions.push_back(ExtensionsProperties[i].extensionName);
    }

    uint32_t LayerCount = 0;
    vkEnumerateInstanceLayerProperties(&LayerCount, nullptr);
    vector<VkLayerProperties> LayersProperties(LayerCount);
    vkEnumerateInstanceLayerProperties(&LayerCount, LayersProperties.data());

    for(int i = 0; i < LayersProperties.size(); i++)
    {
        Layers.push_back(LayersProperties[i].layerName);
    }

    InstanceInfo.enabledExtensionCount = static_cast<uint32_t>(Extensions.size());
    InstanceInfo.ppEnabledExtensionNames = Extensions.data();
    InstanceInfo.enabledLayerCount = static_cast<uint32_t>(LayersProperties.size());
    InstanceInfo.ppEnabledLayerNames = Layers.data();

    vkCreateInstance(&InstanceInfo, nullptr, &Instance);
}
