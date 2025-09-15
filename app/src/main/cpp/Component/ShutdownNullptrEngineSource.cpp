#include"ShutdownNullptrEngineComponent.h"

ShutdownNullptrEngine::ShutdownNullptrEngine(VkInstance Instance, VkDevice Device)
{
    this->ShutdownNullptrEngineDevice(Device);
    this->ShutdownNullptrEngineInstance(Instance);
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