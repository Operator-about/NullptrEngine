#include "GetDataNullptrEngineComponent.h"

//Получение формата по параметрам
void GetDataNullptrEngine::GetFormat(VkPhysicalDevice PhysicalDevice, VkSurfaceKHR Surface, VkColorSpaceKHR Color, VkFormat LFormat)
{
    //Получение всех форматов из устройства
    uint32_t FormatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &FormatCount, nullptr);
    vector<VkSurfaceFormatKHR> LFormats(FormatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &FormatCount, LFormats.data());

    //Получение формата по определённым параметрам
    for(VkSurfaceFormatKHR Format : LFormats)
    {
        if(Format.colorSpace == Color && Format.format == LFormat)
        {
            Formats = Format;
            break;
        }
    }
}

//Получение параметров определённого формата
VkFormatProperties GetDataNullptrEngine::GetFormatProperties(VkPhysicalDevice PhysicalDevice, VkFormat Format)
{
    VkFormatProperties FormatProperties = {};
    vkGetPhysicalDeviceFormatProperties(PhysicalDevice, Format, &FormatProperties);

    return FormatProperties;
}

//Получение параметров формата для изображения по определённым параметрам
VkImageFormatProperties GetDataNullptrEngine::GetImageFormatProperties(VkPhysicalDevice PhysicalDevice, VkFormat Format, VkImageType Type, VkImageTiling Tiling, VkImageUsageFlags Usage, VkImageCreateFlags Flag)
{
    VkImageFormatProperties ImageFormatProperties = {};
    vkGetPhysicalDeviceImageFormatProperties(PhysicalDevice, Format, Type, Tiling, Usage, Flag, &ImageFormatProperties);

    return ImageFormatProperties;
}

//Получение параметров памяти устройства
VkPhysicalDeviceMemoryProperties GetDataNullptrEngine::GetPhysicalDeviceMemoryProperties(VkPhysicalDevice PhysicalDevice)
{
    VkPhysicalDeviceMemoryProperties MemoryProperties = {};
    vkGetPhysicalDeviceMemoryProperties(PhysicalDevice, &MemoryProperties);

    return MemoryProperties;
}

//Получение параметров устройства
VkPhysicalDeviceProperties GetDataNullptrEngine::GetPhysicalDeviceProperties(VkPhysicalDevice PhysicalDevice)
{
    VkPhysicalDeviceProperties PhysicalDeviceProperties = {};
    vkGetPhysicalDeviceProperties(PhysicalDevice, &PhysicalDeviceProperties);

    return PhysicalDeviceProperties;
}

//Получение дополнительных функций из устройства
VkPhysicalDeviceFeatures GetDataNullptrEngine::GetPhysicalDeviceFeatures(VkPhysicalDevice PhysicalDevice)
{
    VkPhysicalDeviceFeatures DeviceFeatures = {};
    vkGetPhysicalDeviceFeatures(PhysicalDevice, &DeviceFeatures);

    return DeviceFeatures;
}

//Получение под-ресурсов изображения
pair<VkImageSubresource, VkSubresourceLayout> GetDataNullptrEngine::GetImageSubresource(VkDevice Device, VkImage Image)
{
    const VkImageSubresource Subresource = {};
    VkSubresourceLayout SubresourceLayout = {};
    vkGetImageSubresourceLayout(Device, Image, &Subresource, &SubresourceLayout);

    return {Subresource, SubresourceLayout};
}
