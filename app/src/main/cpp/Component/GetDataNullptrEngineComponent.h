#ifndef NULLPTRENGINE_GETDATANULLPTRENGINECOMPONENT_H
#define NULLPTRENGINE_GETDATANULLPTRENGINECOMPONENT_H

#include<vulkan/vulkan.h>
#include<vulkan/vulkan_android.h>
#include<iostream>
#include<vector>
#include<string>
#include<utility>
using namespace std;

class GetDataNullptrEngine
{
public:
    VkSurfaceFormatKHR Formats = {};

    void GetFormat(VkPhysicalDevice PhysicalDevice, VkSurfaceKHR Surface, VkColorSpaceKHR Color, VkFormat LFormat);
    VkFormatProperties GetFormatProperties(VkPhysicalDevice PhysicalDevice, VkFormat Format);
    VkImageFormatProperties GetImageFormatProperties(VkPhysicalDevice PhysicalDevice, VkFormat Format, VkImageType Type, VkImageTiling Tiling, VkImageUsageFlags Usage, VkImageCreateFlags Flag);
    VkPhysicalDeviceMemoryProperties GetPhysicalDeviceMemoryProperties(VkPhysicalDevice PhysicalDevice);
    VkPhysicalDeviceProperties GetPhysicalDeviceProperties(VkPhysicalDevice PhysicalDevice);
    VkPhysicalDeviceFeatures GetPhysicalDeviceFeatures(VkPhysicalDevice PhysicalDevice);
    pair<VkImageSubresource, VkSubresourceLayout> GetImageSubresource(VkDevice Device, VkImage Image);
};

#endif //NULLPTRENGINE_GETDATANULLPTRENGINECOMPONENT_H
