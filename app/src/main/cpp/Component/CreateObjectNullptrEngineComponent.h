#ifndef NULLPTRENGINE_CREATEOBJECTNULLPTRENGINECOMPONENT_H
#define NULLPTRENGINE_CREATEOBJECTNULLPTRENGINECOMPONENT_H

#include<vulkan/vulkan.h>
#include<vulkan/vulkan_android.h>
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class CreateObjectNullptrEngine
{
public:
    VkImage CreateImage(VkDevice Device, VkImageType Type, VkFormat Format, VkExtent3D Size, uint32_t MipLevel, uint32_t ArrayLayers,
                        VkSampleCountFlagBits Sample, VkImageTiling Tiling, VkImageUsageFlags Usage, VkSharingMode Mode,
                        uint32_t QueueCount = 0, uint32_t* QueueFamilyIndex = 0);

    VkBuffer CreateBuffer(VkDevice Device, VkDeviceSize Size, VkBufferUsageFlagBits Usage, VkSharingMode Mode, uint32_t QueueCount = 0, uint32_t* QueueFamilyIndex = 0);
};

#endif //NULLPTRENGINE_CREATEOBJECTNULLPTRENGINECOMPONENT_H
