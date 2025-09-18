#include"MemoryManagementNullptrEngineComponent.h"

VkDeviceMemory MemoryManagementNullptrEngine::SetMemoryDevice(VkDevice Device, uint32_t Size, uint32_t MemoryTypeCount)
{
    VkMemoryAllocateInfo MemoryInfo = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            .allocationSize = Size,
            .memoryTypeIndex = MemoryTypeCount
    };

    VkDeviceMemory Memory = {};

    vkAllocateMemory(Device, &MemoryInfo, nullptr, &Memory);

    return Memory;
}

VkDeviceSize MemoryManagementNullptrEngine::GetMemoryDeviceInfo(VkDevice Device, VkDeviceMemory Memory)
{
    VkDeviceSize MemorySize = {};
    vkGetDeviceMemoryCommitment(Device, Memory, &MemorySize);

    return MemorySize;
}

void MemoryManagementNullptrEngine::Free(VkDevice Device, VkDeviceMemory Memory)
{
    vkFreeMemory(Device, Memory, nullptr);
}