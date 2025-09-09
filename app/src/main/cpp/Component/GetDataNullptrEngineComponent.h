#ifndef NULLPTRENGINE_GETDATANULLPTRENGINECOMPONENT_H
#define NULLPTRENGINE_GETDATANULLPTRENGINECOMPONENT_H

#include<vulkan/vulkan.h>
#include<vulkan/vulkan_android.h>
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class GetDataNullptrEngine
{
public:
    VkSurfaceFormatKHR GetFormat(VkPhysicalDevice PhysicalDevice, VkSurfaceKHR Surface, VkColorSpaceKHR Color, VkFormat LFormat);
    VkFormatProperties GetFormatProperties(VkPhysicalDevice PhysicalDevice, VkFormat Format);
    VkImageFormatProperties GetImageFormatProperties(VkPhysicalDevice PhysicalDevice, VkFormat Format, VkImageType Type, VkImageTiling Tiling, VkImageUsageFlags Usage, VkImageCreateFlags Flag);
    VkPhysicalDeviceMemoryProperties GetPhysicalDeviceMemoryProperties(VkPhysicalDevice PhysicalDevice);
    VkPhysicalDeviceProperties GetPhysicalDeviceProperties(VkPhysicalDevice PhysicalDevice);
};

#endif //NULLPTRENGINE_GETDATANULLPTRENGINECOMPONENT_H
