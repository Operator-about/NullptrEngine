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
    void CreateImage(VkDevice Device, VkImage& Image, VkImageType Type, VkFormat Format, VkExtent3D Size, uint32_t MipLevel, uint32_t ArrayLayers,
                        VkSampleCountFlagBits Sample, VkImageTiling Tiling, VkImageUsageFlags Usage, VkSharingMode Mode,
                        uint32_t QueueCount = 0, uint32_t* QueueFamilyIndex = nullptr);

    //Создание абстракции для управления изображением
    //Параметры: устройство, изображение, тип, формат, RGBA компонент, под-ресурсы изображения
    void CreateImageView(VkDevice Device, VkImageView& ImageView, VkImage Image, VkImageViewType Type, VkFormat Format, VkComponentMapping Component, VkImageSubresourceRange Subresource);

    void CreateBufferView(VkDevice Device, VkBufferView& BufferView, VkBuffer Buffer, VkFormat Format, VkDeviceSize Offset, VkDeviceSize Range);

    //Создание буфера, параметры: устройство, размер, сценарий использования, режим взаимодействия, кол-во потоков, потоки
    void CreateBuffer(VkDevice Device, VkBuffer& Buffer, VkDeviceSize Size, VkBufferUsageFlagBits Usage, VkSharingMode Mode, uint32_t QueueCount = 0, uint32_t* QueueFamilyIndex = 0);

    //Создание CommandPool, параметры: устройство, потоки, флаг, Pool
    void CreateCommandPool(VkDevice Device, uint32_t QueueFamily, VkCommandPoolCreateFlags Flag, VkCommandPool& Pool);

    //Выделение CommandBuffer, параметры: устройство, CommandBuffer, Pool, уровень, кол-во
    void AllocationCommandBuffer(VkDevice Device, VkCommandBuffer& Buffer, VkCommandPool Pool, VkCommandBufferLevel Level, uint32_t Count);

    //Запись в CommandBuffer, параметры: CommandBuffer, флаг, источник копирования, цель копирования, кол-во регионов(копирования),
    //начало источника копирования, начало цели копирования, размер данных для копирования
    void WriteCommandBuffer(VkCommandBuffer Buffer, VkCommandBufferUsageFlags Flag, VkBuffer ResourceBuffer, VkBuffer TargetBuffer,
                            uint32_t Regions, VkDeviceSize ResourceOffset, VkDeviceSize TargetOffset, VkDeviceSize Size);

    //Запись изображения, параметры: CommandBuffer, флаг, источник копирования, цель копирования, состояние использования изображения, регионы, точка в CommandBuffer, длина рядов в CommandBuffer,
    //высота изображения в CommandBuffer, под-ресурсы изображения, точка в изображении, размер изображения
    void WriteImage(VkCommandBuffer Buffer, VkCommandBufferUsageFlags Flag, VkBuffer ResourceBuffer, VkImage TargetImage, VkImageLayout TargetLayerImage,
                    uint32_t Regions, VkDeviceSize BufferOffset, uint32_t BufferRowLength, uint32_t BufferImageHeight, VkImageSubresourceLayers Subresource, VkOffset3D ImageOffset, VkExtent3D ImageSize);
};

#endif //NULLPTRENGINE_CREATEOBJECTNULLPTRENGINECOMPONENT_H
