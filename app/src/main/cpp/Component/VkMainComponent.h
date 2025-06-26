#ifndef NULLPTRENGINE_VKMAINCOMPONENT_H
#define NULLPTRENGINE_VKMAINCOMPONENT_H

#include<vulkan/vulkan.h>
#include<vulkan/vulkan_android.h>
#include<iostream>
#include<string>
#include<vector>
#include<android/window.h>
#include<set>
#include<android/log.h>
using namespace std;

class VkMain{
public:
    void VkInitialization();
    void VkInstanceInitialization(VkInstance& Instance, VkInstanceCreateInfo& Info);
    void VkPhysicalDeviceInitialization(VkInstance Instance, VkPhysicalDevice& PhysicalDevice);
    void VkLogicalDeviceInitialization(VkInstance Instance, VkPhysicalDevice PhysicalDevice, VkSurfaceKHR Surface, VkDevice& Device);
    void VkSurfaceInitialization(VkInstance Instance, VkSurfaceKHR& Surface, VkAndroidSurfaceCreateInfoKHR& SurfaceInfo, ANativeWindow* Window);
};


#endif
