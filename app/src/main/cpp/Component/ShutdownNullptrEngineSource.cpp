#include"ShutdownNullptrEngineComponent.h"

ShutdownNullptrEngine::ShutdownNullptrEngine(VkInstance Instance, VkDevice Device)
{
    this->ShutdownNullptrEngineDevice(Device);
    this->ShutdownNullptrEngineInstance(Instance);
}

void ShutdownNullptrEngine::ShutdownNullptrEngineImageView(VkDevice Device, VkImageView ImageView)
{
    vkDestroyImageView(Device, ImageView, nullptr);
}

void ShutdownNullptrEngine::ShutdownNullptrEngineImage(VkDevice Device, VkImage Image)
{
    vkDestroyImage(Device, Image, nullptr);
}

void ShutdownNullptrEngine::ShutdownNullptrEngineBuffer(VkDevice Device, VkBuffer Buffer)
{
    vkDestroyBuffer(Device, Buffer, nullptr);
}

void ShutdownNullptrEngine::ShutdownNullptrEngineDevice(VkDevice Device)
{
    vkDeviceWaitIdle(Device);
    vkDestroyDevice(Device, nullptr);
}

void ShutdownNullptrEngine::ShutdownNullptrEngineInstance(VkInstance Instance)
{
    vkDestroyInstance(Instance, nullptr);
}