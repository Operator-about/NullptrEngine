#ifndef NULLPTRENGINE_CREATEOBJECTNULLPTRENGINECOMPONENT_H
#define NULLPTRENGINE_CREATEOBJECTNULLPTRENGINECOMPONENT_H

#include<vulkan/vulkan.h>
#include<vulkan/vulkan_android.h>
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class CreateObjectNullptrEngine
{
public:
    //Создание изображения, параметры: устройство, тип изображения, формат, размер, уровень пирамиды, слой, сглаживание, метод размещения, сценарий использования, режим взаимодействия,
    //кол-во потоков, потоки
    VkImage CreateImage(VkDevice Device, VkImageType Type, VkFormat Format, VkExtent3D Size, uint32_t MipLevel, uint32_t ArrayLayers,
                        VkSampleCountFlagBits Sample, VkImageTiling Tiling, VkImageUsageFlags Usage, VkSharingMode Mode,
                        uint32_t QueueCount = 0, uint32_t* QueueFamilyIndex = nullptr);

    //Создание абстракции для управления изображением
    //Параметры: устройство, изображение, тип, формат, RGBA компонент, под-ресурсы изображения
    VkImageView CreateImageView(VkDevice Device, VkImage Image, VkImageViewType Type, VkFormat Format, VkComponentMapping Component, VkImageSubresourceRange Subresource);

    VkBufferView CreateBufferView(VkDevice Device, VkBuffer Buffer, VkFormat Format, VkDeviceSize Offset, VkDeviceSize Range);

    //Создание буфера, параметры: устройство, размер, сценарий использования, режим взаимодействия, кол-во потоков, потоки
    VkBuffer CreateBuffer(VkDevice Device, VkDeviceSize Size, VkBufferUsageFlagBits Usage, VkSharingMode Mode, uint32_t QueueCount = 0, uint32_t* QueueFamilyIndex = 0);
};

#endif //NULLPTRENGINE_CREATEOBJECTNULLPTRENGINECOMPONENT_H
