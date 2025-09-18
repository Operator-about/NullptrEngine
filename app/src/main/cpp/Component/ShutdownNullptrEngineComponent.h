#ifndef NULLPTRENGINE_SHUTDOWNNULLPTRENGINECOMPONENT_H
#define NULLPTRENGINE_SHUTDOWNNULLPTRENGINECOMPONENT_H

#include<vulkan/vulkan.h>
#include<vulkan/vulkan_android.h>
#include<iostream>
using namespace std;

class ShutdownNullptrEngine
{
public:
    ShutdownNullptrEngine(VkInstance Instance, VkDevice Device);
    void ShutdownNullptrEngineBuffer(VkDevice Device, VkBuffer Buffer);
    void ShutdownNullptrEngineImage(VkDevice Device, VkImage Image);
    void ShutdownNullptrEngineImageView(VkDevice Device, VkImageView ImageView);
private:
    void ShutdownNullptrEngineInstance(VkInstance Instance);
    void ShutdownNullptrEngineDevice(VkDevice Device);
};


#endif //NULLPTRENGINE_SHUTDOWNNULLPTRENGINECOMPONENT_H
