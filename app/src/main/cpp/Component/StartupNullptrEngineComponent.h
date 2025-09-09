#ifndef NULLPTRENGINE_STARTUPNULLPTRENGINECOMPONENT_H
#define NULLPTRENGINE_STARTUPNULLPTRENGINECOMPONENT_H

#include<vulkan/vulkan.h>
#include<vulkan/vulkan_android.h>
#include<iostream>
#include<vector>
#include<string>
#include<android/native_window.h>
#include<android/native_window_jni.h>
#include<set>
#include"GetDataNullptrEngineComponent.h"
using namespace std;

class StartupNullptrEngine
{
public:
    StartupNullptrEngine(ANativeWindow* Window);
    VkInstance Instance = {};
    VkPhysicalDevice PhysicalDevice = {};
    VkPhysicalDeviceFeatures PhysicalDeviceFeatures = {};
    VkDevice Device = {};
    VkSurfaceKHR Surface = {};
private:
    void StartupNullptrEngineInstance();
    void StartupNullptrEnginePhysicalDevice();
    void StartupNullptrEngineSurface(ANativeWindow* Window);
    void StartupNullptrEngineDevice();

};

#endif //NULLPTRENGINE_STARTUPNULLPTRENGINECOMPONENT_H
