#ifndef NULLPTRENGINE_GETDATANULLPTRENGINECOMPONENT_H
#define NULLPTRENGINE_GETDATANULLPTRENGINECOMPONENT_H

#include<vulkan/vulkan.h>
#include<vulkan/vulkan_android.h>
#include<iostream>
#include<vector>
#include<string>
#include<utility>
using namespace std;

class GetDataNullptrEngine
{
public:
    VkSurfaceFormatKHR Formats = {};

    void GetFormat(VkPhysicalDevice PhysicalDevice, VkSurfaceKHR Surface, VkColorSpaceKHR Color, VkFormat LFormat); //Получение формата по параметрам, параметры: физическое устройство, Surface, тип цвета, формат
    VkFormatProperties GetFormatProperties(VkPhysicalDevice PhysicalDevice, VkFormat Format); //Получение параметров формата, параметры: физзическое устройство, формат
    //Получение параметров формата иззображения по параметрам, параметры: физическое устройство, формат, тип изображения, метод размещения, сценарий использования, флаг
    VkImageFormatProperties GetImageFormatProperties(VkPhysicalDevice PhysicalDevice, VkFormat Format, VkImageType Type, VkImageTiling Tiling, VkImageUsageFlags Usage, VkImageCreateFlags Flag);
    VkPhysicalDeviceMemoryProperties GetPhysicalDeviceMemoryProperties(VkPhysicalDevice PhysicalDevice); //Получение параметров памяти физического устройства, параметры: физическое устройство
    VkPhysicalDeviceProperties GetPhysicalDeviceProperties(VkPhysicalDevice PhysicalDevice); //Получение параметров физического устройства, параметры: физическое устройство
    VkPhysicalDeviceFeatures GetPhysicalDeviceFeatures(VkPhysicalDevice PhysicalDevice); //Получение дополнительных возможностей физического устройства, параметры: физическое устройство
    pair<VkImageSubresource, VkSubresourceLayout> GetImageSubresource(VkDevice Device, VkImage Image); //Получение под-ресурсов изображения, параметры: устройство, изображение
};

#endif //NULLPTRENGINE_GETDATANULLPTRENGINECOMPONENT_H
