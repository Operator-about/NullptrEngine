#ifndef NULLPTRENGINE_GETDATANULLPTRENGINECOMPONENT_H
#define NULLPTRENGINE_GETDATANULLPTRENGINECOMPONENT_H

#include<vulkan/vulkan.h>
#include<vulkan/vulkan_android.h>
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class GetDataNullptrEngine
{
public:
    VkSurfaceFormatKHR Formats = {};

    void GetFormat(VkPhysicalDevice PhysicalDevice, VkSurfaceKHR Surface, VkColorSpaceKHR Color, VkFormat LFormat); //Получение формата по параметрам, параметры: физическое устройство, Surface, тип цвета, формат
    void GetFormatProperties(VkPhysicalDevice PhysicalDevice, VkFormat Format, VkFormatProperties& FormatProperties); //Получение параметров формата, параметры: физзическое устройство, формат
    //Получение параметров формата иззображения по параметрам, параметры: физическое устройство, формат, тип изображения, метод размещения, сценарий использования, флаг
    void GetImageFormatProperties(VkPhysicalDevice PhysicalDevice, VkFormat Format,
                                                     VkImageType Type, VkImageTiling Tiling, VkImageUsageFlags Usage, VkImageCreateFlags Flag, VkImageFormatProperties& ImageFormatProperties);
    //Получение параметров памяти физического устройства, параметры: физическое устройство
    void GetPhysicalDeviceMemoryProperties(VkPhysicalDevice PhysicalDevice, VkPhysicalDeviceMemoryProperties& MemoryProperties);
    void GetPhysicalDeviceProperties(VkPhysicalDevice PhysicalDevice, VkPhysicalDeviceProperties& Properties); //Получение параметров физического устройства, параметры: физическое устройство
    void GetPhysicalDeviceFeatures(VkPhysicalDevice PhysicalDevice, VkPhysicalDeviceFeatures& Features); //Получение дополнительных возможностей физического устройства, параметры: физическое устройство
    void GetImageSubresource(VkDevice Device, VkImage Image, VkImageSubresource& Subresource, VkSubresourceLayout& Layout); //Получение под-ресурсов изображения, параметры: устройство, изображение
    void GetQueue(VkDevice Device, VkQueue& Queue, uint32_t QueueFamily, uint32_t QueueIndex); //Получение экземпляра потока, параметры: устройство, поток, семейство потоков, индекс потока

    //Отправка команд из CommandBuffer на выполнение, параметры: буфер, поток, барьер, светофор, ожидающий светофор, WaitDstStageMask, кол-во команд для выполнения, кол-во CommandBuffer, кол-во светофороф,
    //кол-во ожидающих светофоров
    void CommandSubmit(VkCommandBuffer Buffer, VkQueue Queue, VkFence Fence, VkSemaphore Semaphore, VkSemaphore WaitSemaphore, VkPipelineStageFlags WaitDstStageMask,
                       uint32_t CommandSubmitCount, uint32_t CommandBufferCount, uint32_t SemaphoreCount, uint32_t WaitSemaphoreCount);
};

#endif //NULLPTRENGINE_GETDATANULLPTRENGINECOMPONENT_H
