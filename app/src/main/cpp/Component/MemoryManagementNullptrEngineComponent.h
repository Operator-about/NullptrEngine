#ifndef NULLPTRENGINE_MEMORYMANAGEMENTNULLPTRENGINECOMPONENT_H
#define NULLPTRENGINE_MEMORYMANAGEMENTNULLPTRENGINECOMPONENT_H

#include<vulkan/vulkan.h>
#include<vulkan/vulkan_android.h>
#include<iostream>
using namespace std;

class MemoryManagementNullptrEngine
{
public:
    VkDeviceMemory SetMemoryDevice(VkDevice Device, uint32_t Size, uint32_t MemoryTypeCount);
    VkDeviceSize GetMemoryDeviceInfo(VkDevice Device, VkDeviceMemory Memory);
    void Free(VkDevice Device, VkDeviceMemory Memory);
};

#endif
