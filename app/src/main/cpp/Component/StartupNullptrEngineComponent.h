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
#include"CreateObjectNullptrEngineComponent.h"
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

    uint32_t GraphicsQueueFamily = 0, PresentQueueFamily = 0;
    uint32_t* QueueFamilyIndex;

private:
    GetDataNullptrEngine Data = GetDataNullptrEngine();
    CreateObjectNullptrEngine NewObject = CreateObjectNullptrEngine();

    void StartupNullptrEngineInstance();
    void StartupNullptrEnginePhysicalDevice();
    void StartupNullptrEngineSurface(ANativeWindow* Window);
    void StartupNullptrEngineDevice();

};

#endif //NULLPTRENGINE_STARTUPNULLPTRENGINECOMPONENT_H
