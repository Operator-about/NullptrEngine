#ifndef NULLPTRENGINE_STARTUPNULLPTRENGINECOMPONENT_H
#define NULLPTRENGINE_STARTUPNULLPTRENGINECOMPONENT_H

#include<vulkan/vulkan.h>
#include<vulkan/vulkan_android.h>
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class StartupNullptrEngine
{
public:
    StartupNullptrEngine();
private:
    void StartupNullptrEngineInstance();
    void StartupNullptrEnginePhysicalDevice();
};

#endif //NULLPTRENGINE_STARTUPNULLPTRENGINECOMPONENT_H
