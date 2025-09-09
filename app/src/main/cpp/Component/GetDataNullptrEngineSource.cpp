#include "GetDataNullptrEngineComponent.h"

VkSurfaceFormatKHR GetDataNullptrEngine::GetFormat(VkPhysicalDevice PhysicalDevice, VkSurfaceKHR Surface, VkColorSpaceKHR Color, VkFormat LFormat)
{
    uint32_t FormatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &FormatCount, nullptr);
    vector<VkSurfaceFormatKHR> Formats(FormatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &FormatCount, Formats.data());

    for(auto Format : Formats)
    {
        if(Format.colorSpace == Color && Format.format == LFormat)
        {
            return Format;
        }
    }
}

VkFormatProperties GetDataNullptrEngine::GetFormatProperties(VkPhysicalDevice PhysicalDevice, VkFormat Format)
{
    VkFormatProperties FormatProperties = {};
    vkGetPhysicalDeviceFormatProperties(PhysicalDevice, Format, &FormatProperties);

    return FormatProperties;
}

VkImageFormatProperties GetDataNullptrEngine::GetImageFormatProperties(VkPhysicalDevice PhysicalDevice, VkFormat Format, VkImageType Type, VkImageTiling Tiling, VkImageUsageFlags Usage, VkImageCreateFlags Flag)
{
    VkImageFormatProperties ImageFormatProperties = {};
    vkGetPhysicalDeviceImageFormatProperties(PhysicalDevice, Format, Type, Tiling, Usage, Flag, &ImageFormatProperties);

    return ImageFormatProperties;
}

VkPhysicalDeviceMemoryProperties GetDataNullptrEngine::GetPhysicalDeviceMemoryProperties(VkPhysicalDevice PhysicalDevice)
{
    VkPhysicalDeviceMemoryProperties MemoryProperties = {};
    vkGetPhysicalDeviceMemoryProperties(PhysicalDevice, &MemoryProperties);

    return MemoryProperties;
}

VkPhysicalDeviceProperties GetDataNullptrEngine::GetPhysicalDeviceProperties(VkPhysicalDevice PhysicalDevice)
{
    VkPhysicalDeviceProperties PhysicalDeviceProperties = {};
    vkGetPhysicalDeviceProperties(PhysicalDevice, &PhysicalDeviceProperties);

    return PhysicalDeviceProperties;
}
