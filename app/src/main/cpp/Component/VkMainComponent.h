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

    VkInstance Instance = {};
    VkInstanceCreateInfo Info = {};
    VkPhysicalDevice PhysicalDevice = {};
    VkSurfaceKHR Surface = {};
    VkAndroidSurfaceCreateInfoKHR SurfaceInfo = {};
    vector<const char*> Extensions;

    void VkInitialization();
    void VkInstanceInitialization();
    void VkExtensionsInitialization();
    void VkPhysicalDevicesInitialization();
    void VkLogicalDevicesInitialization();
    void VKSurfaceInitialization();
};


#endif
